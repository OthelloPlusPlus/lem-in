#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    demo.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohengelm <ohengelm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/01 20:50:34 by ohengelm          #+#    #+#              #
#    Updated: 2026/06/05 16:04:15 by ohengelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
#                                 CONFIGURATION
# ==============================================================================

LEMIN=lem-in
VISUALISER=visu-hex

INPUT_FILE=temp_input_file
OUTPUT_FILE=temp_output_file
GENERATOR=generator_linux

C_RED="\033[38;2;255;0;0m"
C_ORANGE="\033[38;2;255;128;0m"
C_YELLOW="\033[38;2;255;255;0m"
C_GREEN="\033[38;2;0;255;0m"
C_RESET="\033[0m"

# ==============================================================================
#                                   FUNCTIONS
# ==============================================================================

run_files()
{
	for map in ./assets/map/*; do
		map_name=$(basename "$map");
		echo "${C_ORANGE}Testing ${map}${C_RESET}"
		case $(basename "${map}") in
			err*)
				./${LEMIN} < ${map} 1> /dev/null && 
				echo "${C_RED}KO${C_RESET}" ||
				echo "${C_GREEN}OK${C_RESET}";;
			*)
				start=$(date +%s%N)
				timeout 15s ./${LEMIN} < ${map} > ${OUTPUT_FILE};
				if [ $? -eq 124 ]; then
					echo "./${LEMIN} < ${map} timed out after 15s";
					exit 1;
				fi
				end=$(date +%s%N)
				cat ${OUTPUT_FILE};

				LINES_REQUIRED=$(grep -m1 'number of lines required' "${map}")
				if [ -n "${LINES_REQUIRED}" ]; then
					echo "${C_YELLOW}${LINES_REQUIRED}${C_RESET}"
				fi

				echo "${C_ORANGE}Duration ${map}${C_RESET}"
				diff=$((end - start))
				printf "%02d:%02d.%09.9d\n"	$((diff / 60000000000))\
										$(((diff / 1000000000) % 60))\
										$((diff % 1000000000))

				echo "${C_ORANGE}Visual ${map}:${C_RESET}";
				./${VISUALISER} < ${OUTPUT_FILE};;
		esac
	done
}

run_generator()
{
	for option in flow-one flow-ten flow-thousand big big-superposition; do
		echo "${C_ORANGE}${GENERATOR} --${option}${C_RESET}"
		./assets/"${GENERATOR}" --"${option}" > "${INPUT_FILE}"

		LINES_REQUIRED=$(grep -m1 'number of lines required' "${INPUT_FILE}")
		echo "${LINES_REQUIRED}"
		LINES_REQUIRED=$(echo "${LINES_REQUIRED}" | grep -oE '[0-9]+')
		timeout 15s ./"${LEMIN}" < ${INPUT_FILE} > ${OUTPUT_FILE}
		if [ $? -eq 124 ]; then
			echo "${C_RED}TIMEOUT${C_RESET}"
			continue;
		fi
		LINE_COUNT=$(grep -E '^L[0-9]+-[[:alnum:]_]+' "${OUTPUT_FILE}" | wc -l)
		echo -n "#Here the number of counted lines is:  "
		if [ "${LINE_COUNT}" -eq "${LINES_REQUIRED}" ]; then
			echo -n "${C_GREEN}";
		elif [ "${LINE_COUNT}" -lt "${LINES_REQUIRED}" ]; then
			echo -n "${C_YELLOW}";
		else
			echo -n "${C_RED}";
		fi
		echo "${LINE_COUNT}${C_RESET}";
	done
}

rerun_big_superposition()
{
	while true; do

		echo "${C_ORANGE}${GENERATOR} --big-superposition${C_RESET}"

		./assets/"${GENERATOR}" --big-superposition > "${INPUT_FILE}"

		LINES_REQUIRED=$(grep -m1 'number of lines required' "${INPUT_FILE}")
		echo "${LINES_REQUIRED}"

		LINES_REQUIRED=$(echo "${LINES_REQUIRED}" | grep -oE '[0-9]+')

		timeout 15s ./"${LEMIN}" < "${INPUT_FILE}" > "${OUTPUT_FILE}"

		if [ $? -eq 124 ]; then
			echo "${C_RED}TIMEOUT${C_RESET}"
			continue
		fi

		LINE_COUNT=$(grep -E '^L[0-9]+-[[:alnum:]_]+' "${OUTPUT_FILE}" | wc -l)

		echo -n "#Here the number of counted lines is:  "
		if [ "${LINE_COUNT}" -eq "${LINES_REQUIRED}" ]; then
			echo -n "${C_GREEN}";
		elif [ "${LINE_COUNT}" -lt "${LINES_REQUIRED}" ]; then
			echo -n "${C_YELLOW}";
		else
			echo -n "${C_RED}";
		fi
		echo "${LINE_COUNT}${C_RESET}";

		# stop when count >= required * 1.1
		if [ $((LINE_COUNT * 100)) -ge $((LINES_REQUIRED * 109)) ]; then
			echo "${C_GREEN}Threshold reached${C_RESET}"
			break
		fi

		echo "${C_YELLOW}Retrying...${C_RESET}"

	done
}

# ==============================================================================
#                               SCRIPT EXECUTION
# ==============================================================================

for executable in "$LEMIN" "$VISUALISER"; do
	if [ ! -x "$executable" ]; then
		echo -n "${C_RED}Error${C_RESET}: " >&2
		if [ ! -e "$executable" ]; then
			echo "$executable is missing. Run ./configure and make" >&2
		else
			echo "$executable is not executable" >&2
		fi
		exit 1
	fi
done

run_files
run_generator
# rerun_big_superposition

rm -f -- "${OUTPUT_FILE}"
rm -f -- "${INPUT_FILE}"

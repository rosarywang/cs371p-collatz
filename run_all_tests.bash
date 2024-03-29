#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo "Cleaning build"
make clean > /dev/null
rm -rf script-results
echo "Rebuilding"
make test > /dev/null
mkdir -p script-results
echo "Pulling new tests"
#git pull
echo "Testing"
for input in /u/msbck263/CS371P/public-repo/collatz-tests/*-RunCollatz.in;
do
	output="${input%.in}.out"
	output="${output##*/}"

	if ! ( ./RunCollatz < $input > ./script-results/$output || false ) 2> /dev/null
	then
		failed_tests="$failed_tests\n$input (assertion triggered)"
		continue
	fi 	
	diff_output="$(diff -qsZ "./script-results/$output" "/u/msbck263/CS371P/public-repo/collatz-tests/$output")"
	if [[ $diff_output == *"differ"* ]] 
	then
		failed_tests="$failed_tests\n${RED}diff ./script-results/$output /u/msbck263/CS371P/public-repo/collatz-tests/$output${NC}"
	else
		passed_tests="$passed_tests\n$input"
	fi
done

echo -e "${GREEN}PASSED${NC}$passed_tests\n"
echo -e "${RED}FAILED${NC}$failed_tests"

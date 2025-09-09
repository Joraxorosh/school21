#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test.txt"
TEST_FILE1="test1.txt"

echo "" > log.txt

for flags in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
          TEST1="$flags $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              echo "$DIFF_RES" >> log.txt
              echo "" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
done

for flags in -b -e -n -s -t -v #-E -T #--number-nonblank --number --squeeze-blank
do
  for flags2 in -b -e -n -s -t -v #-E -T #--number-nonblank --number --squeeze-blank
  do
          TEST1="$flags $flags2 $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              echo "$DIFF_RES" >> log.txt
              echo "" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
  done
done

for flags in -b -e -n -s -t -v #-E -T #--number-nonblank --number --squeeze-blank
do
  for flags2 in -b -e -n -s -t -v #-E -T #--number-nonblank --number --squeeze-blank
  do
      for flags3 in -b -e -n -s -t -v #-E -T #--number-nonblank --number --squeeze-blank
      do
          TEST1="$flags $flags2 $flags3 $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              echo "$DIFF_RES" >> log.txt
              echo "" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
      done
  done
done

for flags1 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
  for flags2 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
  do
      for flags3 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
      do
          for flags4 in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
          do
              TEST1="$flags $flags2 $flags3 $flags4 $TEST_FILE"
              echo "$TEST1"
              ./s21_cat $TEST1 > s21_cat.txt
              cat $TEST1 > cat.txt
              DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
              if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
                then
                  (( COUNTER_SUCCESS++ ))
                else
                  echo "$TEST1" >> log.txt
                  echo "$DIFF_RES" >> log.txt
                  echo "" >> log.txt
                  (( COUNTER_FAIL++ ))
              fi
              rm s21_cat.txt cat.txt
          done
      done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

exit "$COUNTER_FAIL"
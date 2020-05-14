#!/bin/bash
#
#This script outputs command name
#number of parameters
#and what the parameters are
#
echo "The command is $0"
echo "The number of parameters: $#"
set "$*"
echo "List of parameters: $*"


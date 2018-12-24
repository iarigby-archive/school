#!/bin/bash

git status
printf "\n***\n"
git add .
git status
printf "\n***\ninsert commit message:"
read commitmessage
git commit -m "$commitmessage"
printf "\n***\n"
git status
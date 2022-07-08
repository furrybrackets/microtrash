#!/bin/bash
git add --all
echo Message:
read msg
git commit -m "$msg"
git push

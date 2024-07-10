#!/bin/bash
git config core.hooksPath .githooks
git config commit.template .githooks/commit_message_template.txt
git config -l

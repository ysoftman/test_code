#!/bin/sh
ansible -i host testhost1 -u hanadmin -m command -a "ls -ahl"

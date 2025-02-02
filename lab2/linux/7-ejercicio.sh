#!/bin/bash

# Agrega tareas al crontab si no están ya presentes
(crontab -l 2>/dev/null; echo "0 10 * * * ~/update") | sort -u | crontab -
(crontab -l 2>/dev/null; echo "@reboot ~/update") | sort -u | crontab -

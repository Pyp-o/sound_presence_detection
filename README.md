# sound_presence_detection

Collaborateurs: Erwan CHANDLER - Pierre HENRY - Maxime PACAUD

Système de détection de présence et sonore avec récupération et enregistrement des états.
Le système fonctionne avec une RaspBerry Pi3 (maître) qui est en charge du capteur de présence, et du stockage des logs.
Et un Arduino Nano (esclave) se charge des LEDs d'état et du capteur sonore.

# A faire a l'installation
ajouter au crontab la commande suivante: 
  * 22 * * * bash /home/pyp/Documents/presence_detection/gitRepository/sound_presence_detection/logsGitUpdate.sh

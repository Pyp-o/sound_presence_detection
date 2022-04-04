# sound_presence_detection

Collaborateurs: Erwan CHANDLER - Pierre HENRY - Maxime PACAUD

Système de détection de présence et sonore avec récupération et enregistrement des états.
Le système fonctionne avec une RaspBerry Pi3 (maître) qui est en charge du capteur de présence, et du stockage des logs.
Et un Arduino Nano (esclave) se charge des LEDs d'état et du capteur sonore.

# A faire a l'installation
* generer une cle ssh, l'ajouter aux acces du depot git
* configurer un compte github et git ayant les droits pour push dans le depot
* ajouter au crontab la commande permettant de lancer les scripts au demarrage :  logsGitUpdate.sh
  - <* 22 * * * bash /home/user1/Documents/sound_presence_detection/logsGitUpdate.sh>
  - <@reboot bash /home/user1/Documents/sound_presence_detection/main_script.sh>

# Open the first terminal and run script 1
gnome-terminal -- bash -c "./serverM; exec bash"

# Open the second terminal and run script 2
gnome-terminal -- bash -c "./serverCE; exec bash"

# Open the third terminal and run script 3
gnome-terminal -- bash -c "./serverEE; exec bash"

# Open the fourth terminal and run script 4
gnome-terminal -- bash -c "./client; exec bash"

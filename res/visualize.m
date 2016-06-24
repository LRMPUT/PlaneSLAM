gtTraj = load('groundtruth.txt');
odomTraj = load('odomTraj.txt');
optTraj = load('optTraj.txt');

plot3(gtTraj(:, 2), gtTraj(:, 3), gtTraj(:, 4), '.-g');
hold on;
plot3(odomTraj(:, 2), odomTraj(:, 3), odomTraj(:, 4), '.-r');
hold on;
plot3(optTraj(:, 2), optTraj(:, 3), optTraj(:, 4), '.-b');

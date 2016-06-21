gtTraj = load('groundtruth.txt');
diffTraj = load('diffTraj.txt');

plot3(gtTraj(:, 2), gtTraj(:, 3), gtTraj(:, 4), '-r');
hold on;
plot3(diffTraj(:, 2), diffTraj(:, 3), diffTraj(:, 4), '-b');

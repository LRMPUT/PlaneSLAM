gtTraj = load('groundtruth.txt');
odomTraj = load('odomTraj.txt');
optTrajSE3 = load('optTrajSE3.txt');
optTrajMin = load('optTrajMin.txt');

plot3(gtTraj(:, 2), gtTraj(:, 3), gtTraj(:, 4), '.-g');
hold on;
plot3(odomTraj(:, 2), odomTraj(:, 3), odomTraj(:, 4), '.-r');
hold on;
plot3(optTrajSE3(:, 2), optTrajSE3(:, 3), optTrajSE3(:, 4), '.-b');
hold on;
plot3(optTrajMin(:, 2), optTrajMin(:, 3), optTrajMin(:, 4), '.-k');

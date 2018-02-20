planes = load('planes.txt');

%remove 3 walls to see what's inside
%planes([4, 5, 6], :) = [];

plX = planes(:, [2, 5, 8, 11])';
plY = planes(:, [3, 6, 9, 12])';
plZ = planes(:, [4, 7, 10, 13])';

patch(plX, plY, plZ, [0.6 0.6 0.6]);

gtTraj = load('groundtruth.txt');
odomTraj = load('odomTraj.txt');
optTrajSE3 = load('optTrajSE3.txt');
optTrajMin = load('optTrajMin.txt');

hold on;
plot3(gtTraj(:, 2), gtTraj(:, 3), gtTraj(:, 4), '.-g');
hold on;
plot3(odomTraj(:, 2), odomTraj(:, 3), odomTraj(:, 4), '.-r');
hold on;
plot3(optTrajSE3(:, 2), optTrajSE3(:, 3), optTrajSE3(:, 4), '.-b');
hold on;
plot3(optTrajMin(:, 2), optTrajMin(:, 3), optTrajMin(:, 4), '.-k');

axis('equal');


figure
x = [2,3,4,5,6,7,8,9,10];
% DkC+GSYY
y1 = [38.5,35.1,34.2,33.3,31.2,30.5,30.6,30.9,29.6];
plot(x,y1,'b')
hold on

% DMPO+GSYY
y2 = [34.8,26.5,22.2,16.8,13.9,10.7,8.9,9.3,6.3];
plot(x,y2,'r')
hold on

% DCMPO+GSYY
y3 = [38.5,33.5,31.6,29.4,26.9,25.1,24.5,24.5,22.2];
plot(x,y3,'y')
hold on



% DA+DkC
y4 = [29.7,22.4,18.1,15.6,14.1,11.5,11.2,13.4,11.1];
plot(x,y4,'c')
hold on
% DA+DMPO
y5 = [28.3,18.7,12.8,8.4,4.4,3.3,1.9,2.2,0.8];
plot(x,y5,'k')
hold on

% DA+DCMPO
y6 = [29.7,22.5,17.9,15.3,12.7,10.3,9.6,11.3,9.1];
plot(x,y6,'g')
hold on


% DA+OPA
y7 = [93.5,82.3,78.9,62.5,40.1,20.9,7.7,1.2,0];
plot(x,y7,'m')
hold on

% ZLL
y8 = [41.8,39.6,37.0,36.1,33.9,33,33.4,32.7,31.6];
plot(x,y8,'k')
hold on





legend('GSYY+DkC', 'GSYY+DMPO','GSYY+DCMPO' , 'DA+DkC','DA+DMPO','DA+DCMPO','OPA+DA','ZLL+DkC');

xlabel('Number of processors')
ylabel('Acceptance ratio')


xlim([1 11])
ylim([0 100])

figure
x2 = [2,4,5,6,7,8,9,10];
xx = 2:0.1:10;
% DkC+GSYY
z1 = [100,100,100,88.5,1.5,0,0,0];
zz1 = interp1(x2,z1,xx,'cubic');
plot(xx,zz1,'b')
hold on

% DkC+ZLL
z2 = [100,100,100,91.1,6.5,0,0,0];
zz2 = interp1(x2,z2,xx,'cubic');
plot(xx,zz2,'g')
hold on

% DkC+ZLL
z3 = [100,100,88.7,2.4,0,0,0,0];
zz3 = interp1(x2,z3,xx,'cubic');
plot(xx,zz3,'m')
hold on

% DkC+ZLL
z4 = [89.9,52.5,0.1,0,0,0,0,0];
zz4 = interp1(x2,z4,xx,'cubic');
plot(xx,zz4,'k')
hold on

xlim([1 10])
ylim([0 110])
legend('GSYY+DkC', 'ZLL+DkC','DA+DkC' , 'DA+OPA');
xlabel('Utilization')
ylabel('Acceptance ratio')






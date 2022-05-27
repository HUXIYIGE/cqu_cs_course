function [x,fval,status] = intprog(f,A,B,I,Aeq,Beq,lb,ub,e)
%整数规划求解函数 intprog()
%     其中 f为目标函数向量
%     A和B为不等式约束 Aeq与Beq为等式约束
%     I为整数约束
%     lb与ub分别为变量下界与上界
%     x为最优解，fval为最优值
%例子:
%        maximize 20 x1 + 10 x2 
%        S.T.
%                5 x1 + 4 x2 <=24
%                2 x1 + 5 x2 <=13
%                   x1, x2 >=0 
%                   x1, x2是整数
% f=[-20, -10];
% A=[ 5  4; 2 5];
% B=[24; 13];
% lb=[0 0];
% ub=[inf inf];
% I=[1,2];
% e=0.000001;
% [x v s]= IP(f,A,B,I,[],[],lb,ub,,e)
% x = 4     1  v = -90.0000   s = 1
 
% 控制输入参数
if nargin < 9, e = 0.00001;
   if nargin < 8, ub = []; 
      if nargin < 7, lb = []; 
         if nargin < 6, Beq = []; 
            if nargin < 5, Aeq = [];
               if nargin < 4, I = [1:length(f)];
               end, end, end, end, end, end
  
%求解整数规划对应的线性规划,判断是否有解
options = optimset('display','off');
[x0,fval0,exitflag] = linprog(f,A,B,Aeq,Beq,lb,ub,[],options);
if exitflag < 0
    disp('没有合适整数解');
    x = x0;
    fval = fval0;
    status = exitflag;
    return;
else
    %采用分支定界法求解
    bound = inf;
    [x,fval,status] = branchbound(f,A,B,I,x0,fval0,bound,Aeq,Beq,lb,ub,e);
end


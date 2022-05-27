
function [newx,newfval,status,newbound] = branchbound(f,A,B,I,x,fval,bound,Aeq,Beq,lb,ub,e)
 
% 分支定界法求解整数规划
% f,A,B,Aeq,Beq,lb,ub与线性规划相同
% I为整数限制变量的向量
% x为初始解，fval为初始值
options = optimset('display','off');
[x0,fval0,status0]=linprog(f,A,B,Aeq,Beq,lb,ub,[],options);
 
%递归中的最终退出条件
%无解或者解比现有上界大则返回原解
if status0 <= 0 || fval0 >= bound
    newx = x;
    newfval = fval;
    newbound = bound;
    status = status0;
    return;
end
 
%是否为整数解,如果是整数解则返回
intindex = find(abs(x0(I) - round(x0(I))) > e);
if isempty(intindex)
    newx(I) = round(x0(I));
    newfval = fval0;
    newbound = fval0;
    status = 1;
    return;
end
 
%当有非整可行解时，则进行分支求解
%此时必定会有整数解或空解
%找到第一个不满足整数要求的变量
n = I(intindex(1));
addA = zeros(1,length(f));
addA(n) = 1;
%构造第一个分支 x<=floor(x(n))
A = [A;addA];
B = [B,floor(x(n))];
[x1,fval1,status1,bound1] = branchbound(f,A,B,I,x0,fval0,bound,Aeq,Beq,lb,ub,e);
A(end,:) = [];
B(:,end) = [];
%解得第一个分支，若为更优解则替换，若不是则保持原状
 
status = status1;
if status1 > 0 && bound1 < bound
    newx = x1;
    newfval = fval1;
    bound = fval1;
    newbound = bound1;
else
    newx = x0;
    newfval = fval0;
    newbound = bound;
end
 
%构造第二分支
A = [A;-addA];
B = [B,-ceil(x(n))];
[x2,fval2,status2,bound2] = branchbound(f,A,B,I,x0,fval0,bound,Aeq,Beq,lb,ub,e);    
A(end,:) = [];
B(:,end) = [];
 
%解得第二分支，并与第一分支做比较，如果更优则替换
if status2 > 0 && bound2 < bound
    status = status2;
    newx = x2;
    newfval = fval2;
    newbound = bound2;
end


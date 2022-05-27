
function [newx,newfval,status,newbound] = branchbound(f,A,B,I,x,fval,bound,Aeq,Beq,lb,ub,e)
 
% ��֧���編��������滮
% f,A,B,Aeq,Beq,lb,ub�����Թ滮��ͬ
% IΪ�������Ʊ���������
% xΪ��ʼ�⣬fvalΪ��ʼֵ
options = optimset('display','off');
[x0,fval0,status0]=linprog(f,A,B,Aeq,Beq,lb,ub,[],options);
 
%�ݹ��е������˳�����
%�޽���߽�������Ͻ���򷵻�ԭ��
if status0 <= 0 || fval0 >= bound
    newx = x;
    newfval = fval;
    newbound = bound;
    status = status0;
    return;
end
 
%�Ƿ�Ϊ������,������������򷵻�
intindex = find(abs(x0(I) - round(x0(I))) > e);
if isempty(intindex)
    newx(I) = round(x0(I));
    newfval = fval0;
    newbound = fval0;
    status = 1;
    return;
end
 
%���з������н�ʱ������з�֧���
%��ʱ�ض������������ս�
%�ҵ���һ������������Ҫ��ı���
n = I(intindex(1));
addA = zeros(1,length(f));
addA(n) = 1;
%�����һ����֧ x<=floor(x(n))
A = [A;addA];
B = [B,floor(x(n))];
[x1,fval1,status1,bound1] = branchbound(f,A,B,I,x0,fval0,bound,Aeq,Beq,lb,ub,e);
A(end,:) = [];
B(:,end) = [];
%��õ�һ����֧����Ϊ���Ž����滻���������򱣳�ԭ״
 
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
 
%����ڶ���֧
A = [A;-addA];
B = [B,-ceil(x(n))];
[x2,fval2,status2,bound2] = branchbound(f,A,B,I,x0,fval0,bound,Aeq,Beq,lb,ub,e);    
A(end,:) = [];
B(:,end) = [];
 
%��õڶ���֧�������һ��֧���Ƚϣ�����������滻
if status2 > 0 && bound2 < bound
    status = status2;
    newx = x2;
    newfval = fval2;
    newbound = bound2;
end


package ex1;
public class TriangleJudge {

   
    // 输入三个整数作为边，判断是否满足一般三角形、等腰三角形和等边三角形
        public String triangleJudge(int a,int b,int c){
            
            //任意两条边之和大于第三边 且任一边大于0
            if(a+b>c&&a+c>b&&b+c>a&&a>0&&b>0&&c>0){
                if(a==b&&a==c){
                    return "等边三角形";
                }
                else if(a==b||b==c||a==c){
                    return "等腰三角形";
                }
                else{
                    return "一般三角形";
                }
            }
            else{
                return "不能组成三角形";
            }
        }
        
    }
    
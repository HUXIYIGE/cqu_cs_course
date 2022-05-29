package ex1;
public class SearchBall {
    private static int x[]=new int[10];
    public SearchBall(){}
    public void setBWeight(int w[]){
        for(int i=0;i<w.length;i++){
             x[i]=w[i];
        } 
    }
    public String BeginSearch(){
        if(x[0]+x[1]+x[2]+x[3]+x[4]<x[5]+x[6]+x[7]+x[8]+x[9]){
            if(x[1]+x[2]==x[3]+x[4]){
                return "1号是假球";
            }
            if(x[1]+x[2]<x[3]+x[4]){
                if (x[1]<x[2]) {
                    return "2号是假球";
                 }else {
                    return "3号是假球";
                 }
             }else {
                if (x[3]<x[4]){
                    return "4号是假球";
                }
                else{
                    return "5号是假球";
                }
             }
        }else {
            if(x[6]+x[7]==x[8]+x[9]){
                return "6号是假球";
            }
            if(x[6]+x[7]<x[8]+x[9]) {
                if (x[6]<x[7]) {
                    return "7号是假球";
                }else {
                    return "8号是假球";
                }
            }else {
                if (x[8]<x[9]) {
                    return "9号是假球";
                }else {
                    return "10号是假球";
                }
            }
        }
     }
}


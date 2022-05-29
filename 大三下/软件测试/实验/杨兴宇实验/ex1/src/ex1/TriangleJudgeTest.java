
package ex1;
import junit.framework.TestCase;

public class TriangleJudgeTest extends TestCase{

    public void testTriangleJudge(){
        TriangleJudge tj=new TriangleJudge();

        assertEquals("一般三角形", tj.triangleJudge(3, 4, 5));

        assertEquals("不能组成三角形", tj.triangleJudge(0, 1, 2));

        assertEquals("不能组成三角形", tj.triangleJudge(1, 0, 2));

        assertEquals("不能组成三角形", tj.triangleJudge(2, 1, 0));

        assertEquals("不能组成三角形", tj.triangleJudge(1, 2, 3));

        assertEquals("不能组成三角形", tj.triangleJudge(2, 3, 1));

        assertEquals("不能组成三角形", tj.triangleJudge(3, 2, 1));

        assertEquals("等腰三角形", tj.triangleJudge(6, 6, 8));

        assertEquals("等腰三角形", tj.triangleJudge(6, 8, 6));

        assertEquals("等腰三角形", tj.triangleJudge(8, 6, 6));

        assertEquals("等边三角形", tj.triangleJudge(8, 8, 8));

  }
    public static void main(String args[]) {
        junit.textui.TestRunner.run(TriangleJudgeTest.class);
    }
}


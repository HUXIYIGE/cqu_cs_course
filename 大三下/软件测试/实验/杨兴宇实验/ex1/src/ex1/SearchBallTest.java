package ex1;
import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;
class SearchBallTest {
    @Before
    void setUp() throws Exception {
    }
    
    @Test
    void testBeginSearch1() {
        SearchBall ball=new SearchBall();
        int []w= {6,8,8,8,8,8,8,8,8,8};
        ball.setBWeight(w);
        assertEquals("1号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch2() {
        SearchBall ball=new SearchBall();
        int []w= {8,6,8,8,8,8,8,8,8,8};
        ball.setBWeight(w);
        assertEquals("2号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch3() {
        SearchBall ball=new SearchBall();
        int []w= {8,8,6,8,8,8,8,8,8,8};
        ball.setBWeight(w);
        assertEquals("3号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch4() {
        SearchBall ball=new SearchBall();
        int []w= {8,8,8,6,8,8,8,8,8,8};
        ball.setBWeight(w);
        assertEquals("4号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch5() {
        SearchBall ball=new SearchBall();
        int []w= {8,8,8,8,6,8,8,8,8,8};
        ball.setBWeight(w);
        assertEquals("5号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch6() {
        SearchBall ball=new SearchBall();
        int []w= {8,8,8,8,8,6,8,8,8,8};
        ball.setBWeight(w);
        assertEquals("6号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch7() {
        SearchBall ball=new SearchBall();
        int []w= {8,8,8,8,8,8,6,8,8,8};
        ball.setBWeight(w);
        assertEquals("7号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch8() {
        SearchBall ball=new SearchBall();
        int []w= {8,8,8,8,8,8,8,6,8,8};
        ball.setBWeight(w);
        assertEquals("8号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch9() {
        SearchBall ball=new SearchBall();
        int []w= {8,8,8,8,8,8,8,8,6,8};
        ball.setBWeight(w);
        assertEquals("9号是假球",ball.BeginSearch());
    }
    @Test
    void testBeginSearch10() {
        SearchBall ball=new SearchBall();
        int []w= {8,8,8,8,8,8,8,8,8,6};
        ball.setBWeight(w);
        assertEquals("10号是假球",ball.BeginSearch());
    }

}


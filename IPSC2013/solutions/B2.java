import java.io.InputStream;
import java.util.Scanner;

import net.imyoyo.psjava.dp.ItemCalculator;
import net.imyoyo.psjava.dp.Memoization;
import net.imyoyo.psjava.dp.MemoizationFactory;
import net.imyoyo.psjava.dp.SubItem;
import net.imyoyo.psjava.ds.map.JavaHashMapFactory;
import net.imyoyo.psjava.util.ICPCProblemLauncher;
import net.imyoyo.psjava.util.ICPCProblemSolver;


public class B2 implements ICPCProblemSolver {
  
	// 다이나믹으로 점화식이 나오지만, 너무 오래걸린다. 
	// 그런데 작은 수에 대해서 답을 열심히 살펴보니 아주 요상한 식이 나온다. 그래서 한방에 풀수있다.   
	
	@Override
	public void solve(InputStream is) {
		Scanner in = new Scanner(is);
		int casen = in.nextInt();
		for(int i=0;i<casen;i++) {
			long x = in.nextInt();
			long result = calc(x);
			if(x < 10000) // 메모이제이션 짜논게 있으니 검사한번 해본다.
				assertResult(x, result); 
			System.out.println(result);
		}
	}

	private long calc(long x) { // 마법의 식. 왜맞는지 모르겠음..
		if(x % 2 == 0)
			return (x / 2) * (x-1);
		else
			return (x / 2) * x;
	}
	
	private static final MemoizationFactory MF = new MemoizationFactory(new JavaHashMapFactory());
	
	Memoization<Integer, Long> memo = MF.create(new ItemCalculator<Integer, Long>() { // 점화식을 구현한 메모이제이션
		@Override
		public Long calc(Integer key, SubItem<Integer, Long> sub) {
			int x = key;
			if(x == 1) {
				return 0L;
			} else {
				long max = 0;
				for(int k=2;k<=x;k++) {
					int y = x/k;
					int z = x - y;
					long score = y*z + sub.get(y) + sub.get(z);
					max = Math.max(max, score);
				}
				return max;
			}
		}
	});
	
	private void assertResult(long x, long result) {
		if(memo.get((int)x) != result)
			throw new RuntimeException();
	}

	
	public static void main(String[] args) throws Exception {
		ICPCProblemLauncher.launch(new B2(), args);
	}

}

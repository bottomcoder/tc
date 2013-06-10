import java.io.InputStream;
import java.util.Scanner;

import net.imyoyo.psjava.dp.ItemCalculator;
import net.imyoyo.psjava.dp.Memoization;
import net.imyoyo.psjava.dp.MemoizationFactory;
import net.imyoyo.psjava.dp.SubItem;
import net.imyoyo.psjava.ds.map.JavaHashMapFactory;
import net.imyoyo.psjava.util.ICPCProblemLauncher;
import net.imyoyo.psjava.util.ICPCProblemSolver;


public class K2 implements ICPCProblemSolver {
  
	// K1보다 조금 덜 쉬운 다이나믹. 하지만 쉬워... 2단으로 다이나믹이다. 내려오는 
	
	private static final int M = 1000000009;

	private static final MemoizationFactory MF = new MemoizationFactory(new JavaHashMapFactory());
	
	Memoization<Integer, Long> up = MF.create(new ItemCalculator<Integer, Long>() {
		@Override
		public Long calc(Integer index, SubItem<Integer, Long> sub) {
			int size = index;
			if(size == 0) {
				return 1L;
			} else {
				long sum = 0;
				for(int step=1; step<=2; step++) 
					if(size - step >= 0)
						sum = (sum + sub.get(size-step)) % M;;
				return sum;
			}
		}
	});
	
	Memoization<Integer, Long> down = MF.create(new ItemCalculator<Integer, Long>() {
		@Override
		public Long calc(Integer index, SubItem<Integer, Long> sub) {
			int size = index;
			if(size == 0) {
				return 1L;
			} else {
				long sum = 0;
				for(int step=1;step<=4;step++) 
					if(size-step >= 0) 
						sum = (sum + sub.get(size-step) * up.get(step)) % M;
				return sum;
			}
		}
	});
	
	@Override
	public void solve(InputStream is) {
		Scanner in = new Scanner(is);
		int n = in.nextInt();
		for(int i=0;i<n;i++) {
			int size = in.nextInt();
			System.out.println(down.get(size));
		}
	}

	public static void main(String[] args) throws Exception {
		ICPCProblemLauncher.launch(new K2(), args);
	}

}

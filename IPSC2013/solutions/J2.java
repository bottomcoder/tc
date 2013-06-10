import java.util.Set;
import java.util.TreeSet;

import net.imyoyo.psjava.ds.BitUtil;


public class J2 {

  // J2답이 J1답도 되므로 J2만 풀면된다.
	
	// 일단 w,x,y에 문제의 테이블에 에 있는 순서로 각각에 8번의 신호를 게이트에 보냈을 때, 만들어진 boolean sequence가 게이트의 truth table임을 알아두자.
	// 마치 시뮬레이션 같은데, w,x,y에 8번 신호를 넣어서 나오는 새로운 sequence가 게이트의 truth table인것이다. 
	
	// 기본적인 해법은 가능한 256까지의 모든 게이트에 대해 universal한지 각각 검사한다. universal 하면 출력한다. 간단하다. 하나검사하는데 1초정도 걸리더라.
	
	// 그럼 하나의 게이트 G에 대해서 universal 한지 검사하는 방법을 보자.
	// 게이트들을 조합한 것을 하나의 새로운 게이트가 만들어 졌다고 생각하자. 그런 방법으로 새로운 게이트를 계속 생성해냈을 때 256가지의 모든 truth table이 나온다면 universal이다. 
	// 게이트의 조합은 이미 생성된 sequence들 중에서 3개를 선택해서 G에 넣는 것으로 생각할 수 있다. 그럼 새로운 sequence가 나오겠지. 이걸 새로운 게이트라고 생각해서 set에 추가한다.
	// 새로운게 생성될때까지 계속 하는거야 쭉~
	
	public static void main(String[] args) {
		
		for(int gate=0;gate<(1<<8);gate++) {
			Set<Integer> seqs = new TreeSet<Integer>();
			seqs.add(Integer.parseInt("00001111", 2)); // 이렇게 8번의 신호를 각각 w,x,y에 넣는다고 생각한다.
			seqs.add(Integer.parseInt("00110011", 2));
			seqs.add(Integer.parseInt("01010101", 2));

			boolean added;
			do {
				added = false;
				Set<Integer> snapshot = new TreeSet<Integer>(seqs);
				for(int s1 : snapshot) {
					for(int s2 : snapshot) {
						for(int s3 : snapshot) {
							int newSeq = doGate(s1, s2, s3, gate);
							if(!seqs.contains(newSeq)) {
								seqs.add(newSeq);
								added = true;
							}
						}
					}
				}
			} while(added);
			
			if(seqs.size() == 256) {
				for(int j=0;j<8;j++) 
					System.out.print((BitUtil.isSet(gate, j)?"1 ":"0 "));
				System.out.println();				
			}
		}
	}

	private static int doGate(int seq1, int seq2, int seq3, int gate) {
		int res = 0;
		for(int i=0;i<8;i++) {
			boolean b1 = BitUtil.isSet(seq1, i);								
			boolean b2 = BitUtil.isSet(seq2, i);								
			boolean b3 = BitUtil.isSet(seq3, i);
			int pos = (b1?4:0) + (b2?2:0) + (b3?1:0);
			if(BitUtil.isSet(gate, pos))
				res = BitUtil.set(res, i);
		}
		return res;
	}
	
}

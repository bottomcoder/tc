import java.util.HashMap;
import java.util.Scanner;

import com.abbajoa.common.httpclient.Header;
import com.abbajoa.common.httpclient.HttpClient;
import com.abbajoa.common.httpclient.HttpGet;
import com.abbajoa.common.httpclient.HttpResponse;
import com.abbajoa.common.httpclient.KeepAliveHttpClientFactory;
import com.abbajoa.common.httpclient.SocketConnectionData;
import com.abbajoa.common.httpclient.TransferProgressListener;


public class H2 {
  
	// 답은 머리(http response의 헤더)에 있다. 크롬에서 바로 볼수있음.

	public static void main(String[] args) throws Exception {
		HttpClient client = new KeepAliveHttpClientFactory().create(new SocketConnectionData(false, "ipsc.ksp.sk", 80), "1.1", 30*1000, 30*1000, 30*1000);
		
		// /2013/real/problems/h.html 를 요청하면 http 헤더에 어떤 괴물이 초코렛을 주면 답을 알려준다고 한다. 그래서 쿠키에 초코렛을 심어서 보낸다.
		HashMap<String, String> headers1 = new HashMap<String, String>();
		headers1.put("Cookie", "dessert=chocolate");
		HttpResponse r1 = HttpGet.request(client, "/2013/real/problems/h.html", new HashMap<String, String>(), headers1, "UTF-8", TransferProgressListener.EMPTY_LISTENER);
		String header = r1.headers.toString();

		// 그럼 이 괴물이 간단한 더하기 산수문제를 낸다. 그런데 계속 답이 바뀌기 때문에 바로 답을 구해서 알려준다.
		String start = "How much is ";
		Scanner scan = new Scanner(header.substring(header.indexOf(start) + start.length()).replace('?', ' '));
		int v1 = scan.nextInt();
		scan.next();
		int v2 = scan.nextInt();
		int sum = v1 + v2;
		
		// 더하기 결과를 헤더에 심어서 보낸다.
		HashMap<String, String> headers2 = new HashMap<String, String>();
		headers2.put("H2-Answer", sum + "");
		HttpResponse r2 = HttpGet.request(client, "/2013/real/problems/h.html", new HashMap<String, String>(), headers2, "UTF-8", TransferProgressListener.EMPTY_LISTENER);
		for(Header h : r2.headers)
			if(h.key.equals("H2"))
				System.out.println(h.value);
	}

}

// ysoftman
// Redis Java Client Connector - jedis 사용
// jar 다운로드 https://github.com/xetorthio/jedis/downloads
import redis.clients.jedis.Jedis;

public class RedisTest {
	public static void main(String[] args) {
		Jedis jedis = new Jedis("10.101.56.84", 6379);
		// jedis.auth("password");
		
		System.out.println("jedis.dbSize() = " + jedis.dbSize());
		
		// set 해보기
		System.out.println("jedis.set(\"nickname\", \"Hello Redis~\") = " + jedis.set("nickname", "Hello Redis~"));
		
		// get 해보기
		System.out.println("jedis.get(\"nickname\") = " + jedis.get("nickname"));
	}
}

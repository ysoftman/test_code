/////////////////////////////////////////////////////////////
// ysoftman
// Cassandra Client Test (Java + thrift)
// thrift 는 Cassandra 배포(Cassandra/lib/*.jar) 에 포함되어 있음
// 컴파일 및 실행
// export CLASSPATH=/Users/ysoftman/workspace/test_code/CassandraTest/apache-cassandra-1.2.5/lib/*:.
// javac CassandraTest.java
// java CassandraTest
/////////////////////////////////////////////////////////////
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Random;
import java.lang.Math;


import org.apache.cassandra.thrift.Cassandra;
import org.apache.cassandra.thrift.Column;
import org.apache.cassandra.thrift.ColumnOrSuperColumn;
import org.apache.cassandra.thrift.ColumnParent;
import org.apache.cassandra.thrift.ColumnPath;
import org.apache.cassandra.thrift.SuperColumn;
import org.apache.cassandra.thrift.Mutation;
import org.apache.cassandra.thrift.ConsistencyLevel;
import org.apache.cassandra.thrift.InvalidRequestException;
import org.apache.cassandra.thrift.NotFoundException;
import org.apache.cassandra.thrift.SlicePredicate;
import org.apache.cassandra.thrift.SliceRange;
import org.apache.cassandra.thrift.KeyRange;
import org.apache.cassandra.thrift.KeySlice;
import org.apache.cassandra.thrift.TimedOutException;
import org.apache.cassandra.thrift.UnavailableException;
import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.transport.TFramedTransport;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TTransport;

/*
cassandra 0.7 이상 API 를 사용함
# 컬럼패밀리(cf) 생성;
create column family game2 with comparator=UTF8Type and subcomparator=UTF8Type and column_type=Super and key_validation_class=UTF8Type and default_validation_class=UTF8Type;
*/
public class CassandraTest
{
	public static ByteBuffer toByteBuffer(String value) throws UnsupportedEncodingException
	{
		return ByteBuffer.wrap(value.getBytes("UTF-8"));
	}

	public static String toString(ByteBuffer buffer) throws UnsupportedEncodingException
	{
		byte[] bytes = new byte[buffer.remaining()];
		buffer.get(bytes);
		return new String(bytes, "UTF-8");
	}	
	public static void main(String[] args) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		InsertData("127.0.0.1", 9160, "testdb", "col1");
//		Search1("127.0.0.1", 9160, "testdb", "col1");
//		Search2("127.0.0.1", 9160, "testdb", "col1");
//		Search3("127.0.0.1", 9160, "testdb", "col1");
	}
	
	// 대량의 Data Insert 
	public static void InsertData(String ip, int port, String keyspace, String columnfamily) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		long timebefore = 0;
		long timeafter = 0;
		long timeinsert = 0;
				
		// cassandra db 접속하기
		TSocket socket = new TSocket(ip, port);
		socket.setTimeout(10000);
		TTransport tr = new TFramedTransport(socket);
		TProtocol proto = new TBinaryProtocol(tr);
		Cassandra.Client client = new Cassandra.Client(proto);
		tr.open();

		// keyspace 사용
		client.set_keyspace(keyspace);
		
		// 반복적으로 데이터 넣기
		String key_UserNo = "1";
		//ColumnParent parent = new ColumnParent();
		//parent.setColumn_family(columnfamily);
		for (int i=1; i<=100; i++)
		{
			// 키값 자동적으로 증가
			key_UserNo = Integer.toString(i, 10);
			
			SuperColumn supercol = new SuperColumn();
			supercol.setName("Map".getBytes("UTF-8"));
			// MapID 와 Score 컬럼을 반복적으로 저장
			for (int j=1; j<=1000; j++)
			{
				Column colMapID = new Column();
				colMapID.setName(("MapID_"+j).getBytes("UTF-8"));
				colMapID.setValue(toByteBuffer(Long.toString(j, 10)));
				colMapID.setTimestamp(System.currentTimeMillis());
				//client.insert(toByteBuffer(key_UserNo), parent, colMapID, ConsistencyLevel.ONE);
				
				// 랜덤 넘버 생성
				Random r = new Random(System.currentTimeMillis());
				long num = Math.abs((r.nextLong()%1000));
				
				Column colScore = new Column();
				colScore.setName(("Score_"+j).getBytes("UTF-8"));
				colScore.setValue(toByteBuffer(Long.toString(num, 10)));
				colScore.setTimestamp(System.currentTimeMillis());
				//client.insert(toByteBuffer(key_UserNo), parent, colScore, ConsistencyLevel.ONE);
			
				supercol.addToColumns(colMapID);
				supercol.addToColumns(colScore);
			}
			// supercolumn -> mutation 에 추가
			Mutation mutation = new Mutation();
			ColumnOrSuperColumn columnOrsupercolumn = new ColumnOrSuperColumn();
			columnOrsupercolumn.setSuper_column(supercol);
			mutation.setColumn_or_supercolumn(columnOrsupercolumn);
			
			// mutation -> list 에 추가
			List<Mutation> mutationlist = new ArrayList<Mutation>();
			mutationlist.add(mutation);
			
			// list -> map 에 추가
			Map<String, List<Mutation>> mutationlistmap = new HashMap<String, List<Mutation>>();
			// column family 와 mutation list 추가
			mutationlistmap.put(columnfamily, mutationlist);
			
			// map -> map 에 추가
			Map<ByteBuffer, Map<String, List<Mutation>>> data = new HashMap<ByteBuffer, Map<String, List<Mutation>>>();
			// rowkey 와 mutationlistmap 추가
			data.put(toByteBuffer(key_UserNo), mutationlistmap);
			
			timebefore = System.currentTimeMillis();
			client.batch_mutate(data, ConsistencyLevel.ONE);			
			timeafter = System.currentTimeMillis();
			timeinsert = (timeafter-timebefore)/1000;
			
			// insert 시간이 오랜 걸린 경우
			if (timeinsert > 5)
			{
				System.out.println("Data Count:"+i+"   insert time: "+timeinsert+"sec");
			}
			
			// 진행상황 파악을 위해
			if (i%10 == 0)
			{
				System.out.println("Data Count:"+i);
			}
		}
	
		tr.close();
	}
	
	// rowkey 와 컬럼을 주고 값 찾기
	public static void Search1(String ip, int port, String keyspace, String columnfamily) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		// cassandra db 접속하기
		TSocket socket = new TSocket(ip, port);
		socket.setTimeout(10000);
		TTransport tr = new TFramedTransport(socket);
		TProtocol proto = new TBinaryProtocol(tr);
		Cassandra.Client client = new Cassandra.Client(proto);
		tr.open();

		// keyspace 사용
		client.set_keyspace(keyspace);
		
		// rowkey 를 알경우, 해당 로우의 컬럼의 패스 설정하여 조회
		ColumnPath path = new ColumnPath();
		path.setColumn_family(columnfamily);
		path.setSuper_column(toByteBuffer("Map"));
		path.setColumn(toByteBuffer("MapID_1"));
		
		System.out.println(path.getColumn_family());
		ColumnOrSuperColumn result1 = client.get(toByteBuffer("1"), path, ConsistencyLevel.ONE);
		System.out.println(toString(result1.getColumn().value));
		
		tr.close();
	}
	
	// rowkey 를 주고 특정범위의 컬럼에 대한 값 찾기
	public static void Search2(String ip, int port, String keyspace, String columnfamily) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		// cassandra db 접속하기
		TSocket socket = new TSocket(ip, port);
		socket.setTimeout(10000);
		TTransport tr = new TFramedTransport(socket);
		TProtocol proto = new TBinaryProtocol(tr);
		Cassandra.Client client = new Cassandra.Client(proto);
		tr.open();
		
		// keyspace 사용
		client.set_keyspace(keyspace);
		
		// rowkey 를 알경우, 해당 로우의 전체 데이터 조회
		ColumnParent parent = new ColumnParent();
		parent.setColumn_family(columnfamily);
		parent.setSuper_column(toByteBuffer("Map"));
		
		SlicePredicate predicate = new SlicePredicate();
		// 검색할 컬럼 범위 지정
		// 모든 컬럼		 
		//SliceRange sliceRange = new SliceRange(toByteBuffer(""), toByteBuffer(""), false, 10000);
		// 특정 범위의 컬럼
		SliceRange sliceRange = new SliceRange(toByteBuffer("Score_1"), toByteBuffer("Score_1000"), false, 10000);
		predicate.setSlice_range(sliceRange);

		List<ColumnOrSuperColumn> result2 = client.get_slice(toByteBuffer("1"), parent, predicate, ConsistencyLevel.ONE);
		int i = 0;
		for (i=0; i<result2.size(); i++)
		{
			Column column = result2.get(i).column;
			System.out.println(toString(column.name) + " -> " + toString(column.value));
		}
		System.out.println("Count Column: "+i);

		tr.close();
	}
		
	// 전체 row 에서 특정 컬럼의 값을 찾기
	// 찾은 값들 중에서 조건이상 컬럼 카운트하기
	public static void Search3(String ip, int port, String keyspace, String columnfamily) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		// cassandra db 접속하기
		TSocket socket = new TSocket(ip, port);
		// 데이터가 많으면 시간이 오래 걸려 timeout 을 넉넉하게 준다.
		socket.setTimeout(1000000);
		TTransport tr = new TFramedTransport(socket);
		TProtocol proto = new TBinaryProtocol(tr);
		Cassandra.Client client = new Cassandra.Client(proto);
		tr.open();
		
		// keyspace 사용
		client.set_keyspace(keyspace);
	
		// 전체 로우를 대상으로 데이터 조회 
		ColumnParent parent = new ColumnParent();
		parent.setColumn_family(columnfamily);
		parent.setSuper_column(toByteBuffer("Map"));
		
		SlicePredicate predicate = new SlicePredicate();
		// 검색할 컬럼 범위 지정
		// 모든 컬럼
		//SliceRange sliceRange = new SliceRange(toByteBuffer(""), toByteBuffer(""), false, 10000);
		// 특정 범위의 컬럼
		SliceRange sliceRange = new SliceRange(toByteBuffer("Score_1000"), toByteBuffer("Score_1000"), false, 10000);
		predicate.setSlice_range(sliceRange);
				
		KeyRange kr = new KeyRange();
		kr.setCount(100000);
		// 모든 키에 대해서
		//kr.start_key = toByteBuffer("");
		//kr.end_key = toByteBuffer("");
		kr.setStart_key(toByteBuffer(""));
		kr.setEnd_key(toByteBuffer(""));
		
		long timebefore = 0;
		long timeafter = 0;
		long timefetch = 0;
		long timesearch = 0;
		timebefore = System.currentTimeMillis();
		List<KeySlice> rows = client.get_range_slices(parent, predicate, kr, ConsistencyLevel.ONE);
		timeafter = System.currentTimeMillis();
		timefetch = (timeafter-timebefore)/1000;
		int i = 0;
		int cntCol = 0;
		timebefore = System.currentTimeMillis();
		for (i=0; i<rows.size(); i++)
		{
			KeySlice ks = rows.get(i);
			// 각 로우의 컬럼 출력
			List<ColumnOrSuperColumn> temp = ks.getColumns();
			//System.out.print("rowkey["+i+"]"  );
			int j;
			for (j=0; j<temp.size(); j++)
			{
				Column column = temp.get(j).column;
				String colname = toString(column.name);
				System.out.println("Column name : " + colname);
				long colvalue = Long.parseLong(toString(column.value)); 
				//System.out.print(colname + " -> " + colvalue + "    ");
				
				// 컬럼 값이 500 인상이면 카운트
				if (colvalue >= 500)
				{
					cntCol++;
					//System.out.print("checked    ");
				}
			}
			//System.out.print("\n");
		}
		
		timeafter = System.currentTimeMillis();
		timesearch = (timeafter-timebefore)/1000;
				
		System.out.println("all rows: "+rows.size() +", colvalue>=500 : "+cntCol);
		System.out.println("Elapsed Time -> fetch:"+ timefetch + "sec + search: "+timesearch+"sec");
	
		tr.close();
	}
}


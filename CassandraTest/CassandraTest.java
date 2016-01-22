/*
# ysoftman
# Cassandra ���� ��ġ

# �ٿ�ε�
wget http://mirror.apache-kr.org/cassandra/1.2.5/apache-cassandra-1.2.5-bin.tar.gz
tar zxvf apache-cassandra-1.2.5-bin.tar.gz
cd apache-cassandra-1.2.5
 
# ���� ����
vi conf/cassandra.yaml
data_file_directories:
    - /home/ysoftman/apache-cassandra-1.2.5/ysoftman_db/data
commitlog_directory: /home/ysoftman/apache-cassandra-1.2.5/ysoftman_db/commitlog
saved_caches_directory: /home/ysoftman/apache-cassandra-1.2.5/ysoftman_db/saved_caches
rpc_port: 0.0.0.0
rpc_port: 30000

vi conf/log4j-server.properties
log4j.appender.R.File=/home/ysoftman/apache-cassandra-1.2.5/ysoftman_db/log/system.log

# Cassandra ���� �ϱ�
# JDK ��ġ(http://www.oracle.com/technetwork/java/javase/downloads/index.html)
 
# ���� ó�� set
set CASSANDRA_HOME=/home/ysoftman/apache-cassandra-1.2.5

# Cassandra node tool
# ��ũ ���� ����
bin/nodetool -h localhost flush

# ��û �۾� ���� ����
bin/nodetool -h localhost tpstats

# thrift ���� ����
bin/nodetool -h localhost statusthrift

# cfg ���� ����(db ũ���..)
bin/nodetool -h localhost cfstats

#Cassandra ����
bin/cassandra -f > null &

# Cassandra �����ϱ�
# Cassandra-cli (Command Line Interface) �����ϰ� �����ϱ�(��Ʈ 30000 ���)
bin/cassandra-cli
connect localhost/30000;

# �Ǵ� �ѹ��� �����ϸ鼭 �����ϱ�
bin/cassandra-cli --host localhost --port 30000

# Ŭ������ ��� ����
show cluster name;

# Ű�����̽� ��� ����
show keyspaces;

# Ű�����̽� ����
create keyspace testdb;

# Ű�����̽� ����
drop keyspace testdb;

# Ű�����̽� ����
use testdb;

# �÷��йи�(cf) ����
create column family col1 with comparator=UTF8Type and subcomparator=UTF8Type and column_type=Super and key_validation_class=UTF8Type and default_validation_class=UTF8Type;

# cf �� rows_cache ũ�� ����
update column family col1 with rows_cached=5000;

# cf �� keys_cache ũ�� ����
update column family col1 with keys_cached=2000;

# cf �� secondary index ����
# rowkey �� ù��° �ε���
# super column �� �ε��� ���� �ȵ�
update column family col1 with column_metadata= [{column_name:temp, validation_class:UTF8Type, index_type:KEYS}];

# cf=col1�� rowkey=1234, super�÷�=Map, MapID_100�÷�=1000 ����
set col1[1234][Map][MapID_100]='1000';

# cf=col1�� rowkey=1234, super�÷�=Map, Score_100�÷�=100 ����
set col1[1234][Map][Socre_100]=100;

# cf=col1�� rowkey=1234, ��� �÷� ��ȸ
get col1[1234];

# cf=col1�� rowkey=1234, �÷� 10�� ������ ��ȸ
get col1[1234] limit 10;

# cf=col1�� rowkey=1234, Map�� Score_100 �÷� ����
del col1[1234][Map][Score_100];

# cf=col1�� rowkey=1234, �������� ��� �÷� ����
del col1[1234];

# cf col1 ��� ������ 1000 ������ ��ȸ
list col1 limit 1000

# cf=col1�� rowkey=1234, �÷� ����
count col1[1234];
*/

//////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Cassandra Client Test (Java + thrift)
// thrift �� Cassandra ����(Cassandra/lib/*.jar) �� ���ԵǾ� ����
//////////////////////////////////////////////////////////////////////////////////
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
cassandra 0.7 �̻� API �� �����
# �÷��йи�(cf) ����;
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
		InsertData("10.10.10.100", 30000, "testdb", "col1");
//		Search1("10.10.10.100", 30000, "testdb", "col1");
//		Search2("10.10.10.100", 30000, "testdb", "col1");
//		Search3("10.10.10.100", 30000, "testdb", "col1");
	}
	
	// �뷮�� Data Insert 
	public static void InsertData(String ip, int port, String keyspace, String columnfamily) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		long timebefore = 0;
		long timeafter = 0;
		long timeinsert = 0;
				
		// cassandra db �����ϱ�
		TSocket socket = new TSocket(ip, port);
		socket.setTimeout(10000);
		TTransport tr = new TFramedTransport(socket);
		TProtocol proto = new TBinaryProtocol(tr);
		Cassandra.Client client = new Cassandra.Client(proto);
		tr.open();

		// keyspace ���
		client.set_keyspace(keyspace);
		
		// �ݺ������� ������ �ֱ�
		String key_UserNo = "1";
		//ColumnParent parent = new ColumnParent();
		//parent.setColumn_family(columnfamily);
		for (int i=1; i<=100; i++)
		{
			// Ű�� �ڵ������� ����
			key_UserNo = Integer.toString(i, 10);
			
			SuperColumn supercol = new SuperColumn();
			supercol.setName("Map".getBytes("UTF-8"));
			// MapID �� Score �÷��� �ݺ������� ����
			for (int j=1; j<=1000; j++)
			{
				Column colMapID = new Column();
				colMapID.setName(("MapID_"+j).getBytes("UTF-8"));
				colMapID.setValue(toByteBuffer(Long.toString(j, 10)));
				colMapID.setTimestamp(System.currentTimeMillis());
				//client.insert(toByteBuffer(key_UserNo), parent, colMapID, ConsistencyLevel.ONE);
				
				// ���� �ѹ� ����
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
			// supercolumn -> mutation �� �߰�
			Mutation mutation = new Mutation();
			ColumnOrSuperColumn columnOrsupercolumn = new ColumnOrSuperColumn();
			columnOrsupercolumn.setSuper_column(supercol);
			mutation.setColumn_or_supercolumn(columnOrsupercolumn);
			
			// mutation -> list �� �߰�
			List<Mutation> mutationlist = new ArrayList<Mutation>();
			mutationlist.add(mutation);
			
			// list -> map �� �߰�
			Map<String, List<Mutation>> mutationlistmap = new HashMap<String, List<Mutation>>();
			// column family �� mutation list �߰�
			mutationlistmap.put(columnfamily, mutationlist);
			
			// map -> map �� �߰�
			Map<ByteBuffer, Map<String, List<Mutation>>> data = new HashMap<ByteBuffer, Map<String, List<Mutation>>>();
			// rowkey �� mutationlistmap �߰�
			data.put(toByteBuffer(key_UserNo), mutationlistmap);
			
			timebefore = System.currentTimeMillis();
			client.batch_mutate(data, ConsistencyLevel.ONE);			
			timeafter = System.currentTimeMillis();
			timeinsert = (timeafter-timebefore)/1000;
			
			// insert �ð��� ���� �ɸ� ���
			if (timeinsert > 5)
			{
				System.out.println("Data Count:"+i+"   insert time: "+timeinsert+"sec");
			}
			
			// �����Ȳ �ľ��� ����
			if (i%10 == 0)
			{
				System.out.println("Data Count:"+i);
			}
		}
	
		tr.close();
	}
	
	// rowkey �� �÷��� �ְ� �� ã��
	public static void Search1(String ip, int port, String keyspace, String columnfamily) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		// cassandra db �����ϱ�
		TSocket socket = new TSocket(ip, port);
		socket.setTimeout(10000);
		TTransport tr = new TFramedTransport(socket);
		TProtocol proto = new TBinaryProtocol(tr);
		Cassandra.Client client = new Cassandra.Client(proto);
		tr.open();

		// keyspace ���
		client.set_keyspace(keyspace);
		
		// rowkey �� �˰��, �ش� �ο��� �÷��� �н� �����Ͽ� ��ȸ
		ColumnPath path = new ColumnPath();
		path.setColumn_family(columnfamily);
		path.setSuper_column(toByteBuffer("Map"));
		path.setColumn(toByteBuffer("MapID_1"));
		
		System.out.println(path.getColumn_family());
		ColumnOrSuperColumn result1 = client.get(toByteBuffer("1"), path, ConsistencyLevel.ONE);
		System.out.println(toString(result1.getColumn().value));
		
		tr.close();
	}
	
	// rowkey �� �ְ� Ư�������� �÷��� ���� �� ã��
	public static void Search2(String ip, int port, String keyspace, String columnfamily) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		// cassandra db �����ϱ�
		TSocket socket = new TSocket(ip, port);
		socket.setTimeout(10000);
		TTransport tr = new TFramedTransport(socket);
		TProtocol proto = new TBinaryProtocol(tr);
		Cassandra.Client client = new Cassandra.Client(proto);
		tr.open();
		
		// keyspace ���
		client.set_keyspace(keyspace);
		
		// rowkey �� �˰��, �ش� �ο��� ��ü ������ ��ȸ
		ColumnParent parent = new ColumnParent();
		parent.setColumn_family(columnfamily);
		parent.setSuper_column(toByteBuffer("Map"));
		
		SlicePredicate predicate = new SlicePredicate();
		// �˻��� �÷� ���� ����
		// ��� �÷�		 
		//SliceRange sliceRange = new SliceRange(toByteBuffer(""), toByteBuffer(""), false, 10000);
		// Ư�� ������ �÷�
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
		
	// ��ü row ���� Ư�� �÷��� ���� ã��
	// ã�� ���� �߿��� �����̻� �÷� ī��Ʈ�ϱ�
	public static void Search3(String ip, int port, String keyspace, String columnfamily) throws TException, InvalidRequestException, UnavailableException, UnsupportedEncodingException, NotFoundException, TimedOutException
	{
		// cassandra db �����ϱ�
		TSocket socket = new TSocket(ip, port);
		// �����Ͱ� ������ �ð��� ���� �ɷ� timeout �� �˳��ϰ� �ش�.
		socket.setTimeout(1000000);
		TTransport tr = new TFramedTransport(socket);
		TProtocol proto = new TBinaryProtocol(tr);
		Cassandra.Client client = new Cassandra.Client(proto);
		tr.open();
		
		// keyspace ���
		client.set_keyspace(keyspace);
	
		// ��ü �ο츦 ������� ������ ��ȸ 
		ColumnParent parent = new ColumnParent();
		parent.setColumn_family(columnfamily);
		parent.setSuper_column(toByteBuffer("Map"));
		
		SlicePredicate predicate = new SlicePredicate();
		// �˻��� �÷� ���� ����
		// ��� �÷�
		//SliceRange sliceRange = new SliceRange(toByteBuffer(""), toByteBuffer(""), false, 10000);
		// Ư�� ������ �÷�
		SliceRange sliceRange = new SliceRange(toByteBuffer("Score_1000"), toByteBuffer("Score_1000"), false, 10000);
		predicate.setSlice_range(sliceRange);
				
		KeyRange kr = new KeyRange();
		kr.setCount(100000);
		// ��� Ű�� ���ؼ�
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
			// �� �ο��� �÷� ���
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
				
				// �÷� ���� 500 �λ��̸� ī��Ʈ
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


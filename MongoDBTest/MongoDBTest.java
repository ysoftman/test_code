/*
# ysoftman
# MongoDB �˾Ƶα�

# ���� �ڷ�
# http://www.mongodb.org/display/DOCS/Replication
# http://en.wikipedia.org/wiki/MongoDB
# http://docs.mongodb.org/manual/faq/developers/#when-does-mongodb-write-updates-to-disk
 
# Memory Mapped File �̶�
# ����޸��� �Ѻκ����� ������ �޸𸮿� �����Ͽ� �����
# ���� �޸𸮿� ���ε� ������ �޸�ó�� �ٷ��.
# MongoDB ������ ����޸� ������ �������� OS �� ����

# Write �߻���
# �޸𸮿� ���� write �� ��׶��� ������� 1�� �ֱ�� Disk ���(write back)
# disk ��� ���� �߻��� ������ ���Ƿ� ���� �ϰ����� ���� �� ����

# Read �߻��� 
# �޸𸮿� �ε��� ���� ���¿��� read ����

# Mongodb �ӵ��� �ε��� ������� �޸𸮿� �¿�
# �޸𸮰� �������� ����޸𸮸��� ����� ���, ������ ó���ӵ� �ް�

# ���� ����
# master server : �б�, ����� ��� 
# slave server : �б�θ� ���, master ����(���)�ϰ� ����
# arbiter server : master, slave üũ�ϰ�, ��� �߻��� slave �ϳ��� master �� ����

# �⺻������ master �� write �� �����ϱ� ������ master �� write ���ϰ� ����
# �̸� �ذ��ϱ� ���ؼ� �����͸� �л������ϴ� auto-sharding �� �̿�

# 2���� Replication ��� ����
# master-slave
# master 1�뿡 n���� slave �� �پ �����Ѵ�.
# slave �� master �� �����͸� ī���ϰ� �б������̳� ����뵵�θ� ����Ѵ�.(not writes)
                 
# replica-set
# mongodb 1.6 ���ĺ��� �����Ǳ� �����ߴ�.
# master-slave ������ arbiter(master, slave �� heartbeat �� üũ�Ͽ� master ��� �߻��� ��ü������ slave �� �ϳ��� master �� ����) ��带 �߰��Ͽ� fail-over ����
*/

/*
# ysoftman
# MongoDB ���� �ϱ�
# ������ http://www.mongodb.org/display/DOCSKR/Introduction
# client(application) �� router Server �� �����ؼ� ������ ��û�ϸ� �ȴ�.
# client �� write ��û�� �ߴٸ� router �� master mongodb ��, read �ߴٸ� slave mongodb �� �ȳ��Ѵ�.
# mongodb ������ 1000�� ���� ��Ʈ�� �����ϸ� MongoDB ����͸� ���� �� �� �ִ�.(http://127.0.0.1:56555)

# mkdir ysoftman_db_master
# mkdir ysoftman_db_slave
# mkdir ysoftman_db_config

# .lock ���� ����
rm -rfv ./ysoftman_db_master/*.lock
rm -rfv ./ysoftman_db_slave/*.lock
rm -rfv ./ysoftman_db_config/*.lock

# master mongoDB Server �����ϱ�
bin/mongod --master --dbpath ./ysoftman_db_master --port 10010 > /dev/null &

# slave mongoDB Server �����ϱ�(master �� �ٸ� ��񿡼�)
#bin/mongod --slave --dbpath ./ysoftman_db_slave --port 10020 --source 10.10.10.100:10010 --autoresync > /dev/null &

# config mongoDB Server �����ϱ�
bin/mongod --dbpath ./ysoftman_db_config --port 10001 > /dev/null &

# router Server �����ϱ�
bin/mongos --port 10000 --configdb 10.10.10.100:10001 > /dev/null &

# router Server �����ؼ� Sharding �ϱ�
bin/mongo 10.10.10.100:10000


# admin db �� ����ؼ� �����ؾ� �Ѵ�.
use admin;

# shard �߰��ϱ�, router �� ���� �ӽ��� shard �� ����� �� �ֵ��� �ɼ� ���
# ���� ���ÿ��� router �� �ٸ� �ӽ��� shard �� ����ؾ� �Ѵ�.
db.runCommand({addshard:"10.10.10.100:10010", allowLocal:true});

# database �������� sharding enable �ϱ�
db.runCommand({enablesharding:"testdb"});

# col1 collection �� _id ���� �ڵ� �л�Ǿ� �����ϵ��� �ϱ�
db.runCommand({shardcollection:"testdb.col1", key:{"_id":1}});

# sharding ����Ȯ��
db.printShardingStatus();

# shard �����ϱ�
db.runCommand({removeshard:"10.10.10.100:10010"});

# testdb ����ϱ�(DB �� �̸� �������� �ʴ´�.)
use testdb

# routerinfo �ݷ��� ����
db.createCollection("routerinfo");

# ��) JSON �������� ���� �߰�
db.routerinfo.save(
{"id": "1234",
"name": "ysoftman", 
"timestamp": 12345,
"userkey": "UserNo",
"metainfo": {"list":[ 
					{"name":"UserNo", "desc":"�����", "type":"int"},
					{"name":"Item", "desc":"������", "list":[
														{"name":"a", "desc":"������1"},
														{"name":"b", "desc":"������2"}
														]
					},
					{"name":"phone", "desc":"��ȭ��ȣ", "type":"int"},
					{"name":"name", "desc":"�̸�"},
					{"name":"trash", "desc":"������"},
					{"name":"Map", "desc":"��", "pk":"MapID", "array":[
																	{"name":"MapID", "desc":"�ʹ�ȣ", "type":"int"},
																	{"name":"MinScore", "desc":"�ּ�����", "type":"int"},
																	{"name":"MaxScore", "desc":"�ִ�����", "type":"int"}
																]
					}
					]
			}
}
);

# Mongodb ���� ��
# SQL to mongdo mapping chart http://www.mongodb.org/display/DOCS/SQL+to+Mongo+Mapping+Chart
# SQL to Shell to C++ http://www.mongodb.org/pages/viewpage.action?pageId=21270051
# Manual http://www.mongodb.org/display/DOCS/Manual
# MySQL term	Mongo term
# database	database
# table		collection
# index		index
# row		BSON document
# �ϳ��� document �ִ� ũ�� 16MB
 
# Ŭ���̾�Ʈ �����ϱ�
bin\mongo 10.10.10.100:10000
 
# ����
help()
 
# Database ��Ϻ���
show dbs

# testdb ����ϱ�(DB �� �̸� �������� �ʴ´�.)
use testdb
 
# ���� ������� DB Ȯ��
db.getName()

# ���� Databse �÷��� ����
show collections
 
# ũ�� ���� �����Ͽ� �÷��� ���� size: ũ��, max: �ִ� ����
#db.createCollection("col1", {capped:true, size:100000, max: 1000});
db.createCollection("col1");
 
# �÷��� �̸��� ���ڷ� �����ϸ� 
db["1234"]
# �÷��� �̸��� ���ڷ� �����ϸ�
db["col1"] �Ǵ� db.col1
 
# �÷��� ���� ����
db.col1.validate()

# �̷��� �����ϱ�
db.col1.drop()

# col1 ��� �÷��ǿ� Name, URL, LastUpdate ���� �����͸� �����ϱ�(insert() or save())
db.col1.save({UserNo:0, Map:[{MapID:1, Score:100}, {MapID:2, Score:200}]});

# col1 �� ��ť��Ʈ ���� �ľ��ϱ�
db.col1.count()

# col1 �� ��� ��ť��Ʈ �˻��ϱ�
db.col1.find()

# col1 �� ��� ��ť��Ʈ �˻��ϱ�(�鿩�����Ͽ� ���)
db.col1.find().pretty()

# UserNo �� 555 �� ��ť��Ʈ ã��
db.col1.find({UserNo:555})

# UserNo �� 555 �� ��ť��Ʈ�� ã�Ƽ� Map.MapID �ʵ常 �����ֱ�
db.col1.find({"UserNo":555}, {"Map.MapID":1});

# UserNo �� 555 �� ��ť��Ʈ�� ã�Ƽ� _id �� �����ϰ� Map.MapID �ʵ常 �����ֱ�
db.col1.find({"UserNo":555}, {_id:0, "Map.MapID":1});

# col1 �� ��� ��ť��Ʈ �˻��ϱ�(_id �� �������� ���ķ� �����ֱ� -1�̸� ��������)
db.col1.find().sort({_id:1})

# Map.MapID �� ���� 10 �� ��ť��Ʈ ����
db.col1.find({"Map.MapID":10}).count()

# Map.MapID �� ���� 100 ���� ū�ų� ���� ��ť��Ʈ ����
db.col1.find({"Map.MapID":{$gte:100}}).count()

# UserNo �� 555 �̰� Map �迭�� ù��° MapID ���� 1234 �� �����ϱ�(���ǿ� �ش��ϴ� ������ ������ ��ť��Ʈ �ϳ��� �߰��ȴ�)
db.col1.update({"UserNo":555}, {$set:{"Map.0.MapID":1234}}, true);

# UserNo �� 555 �̰� Map �迭�� 100��° MapID ���� �����ϱ�
db.col1.update({"UserNo":555}, {$unset:{"Map.100.MapID":1}});

# UserNo �� 555 �̰� Map �迭�� MapID �� 2�� ���� ã�Ƴ��� 123 ������ �����Ѵ�.
db.col1.update({UserNo:555, "Map.MapID":2}, {$set:{"Map.$.MapID":123}})

# UserNo �� 555 �̰� Map �迭�� object �߰�(array �ʵ忡 ���ؼ��� ����� �� �ִ�)
db.col1.update({UserNo:555}, {$push:{Map:{"MapID":333, "MinScore":300, "MaxScore":500}}})

# ���� �÷����� ������ �ϳ� �����ϱ�(�˻� ��� id�� �����)
db.col1.remove({_id:ObjectId("4d5a1ad2e812000000000515")})

# ���� �÷����� ��� document ����
db.col1.remove()

# �ε��� ����(1:ascending, -1:descending)
db.col1.ensureIndex({"UserNo":1});

# ���� �ε��� Ȯ��(db.system.indexes.find() ��ü �ε��� Ȯ��)
db.col1.getIndexes()

# �ε��� ����
db.col1.dropIndexes()

# db ���� Ȯ��(data, index ������ ��...)
db.stats();

# ���� ���� Ȯ��
db.serverStatus()
db.serverStatus().mem
db.serverStatus().extra_info

# Ŭ���̾�Ʈ ����
exit
*/

/*
////////////////////////////////////////////////////////////////////////////////
// ysoftman
// MongoDB Test - Stored JavaScript ���
////////////////////////////////////////////////////////////////////////////////
# Ŭ���̾�Ʈ �����ϱ�
bin\mongo 10.10.10.100:10000

# testdb ����ϱ�(DB �� �̸� �������� �ʴ´�.)
use testdb
 
# collection �� document ��ü ����
function test1 () {
	db.col1.drop();
	return true;
}
db.eval(test1);


// insert �ϱ� ������ ũ�Ⱑ 4GB �� �Ѿ�� 64bit mongodb ���
// 100����(mongovue)			����ð�: 2�� 35��	DBũ��: 0.5GB
// 1000����(mongovue)			����ð�: 47��15��	DBũ��: 5.95GB	(�ε��� �޸𸮿� ����Ǿ� ���)
function test2() {
	for (var i=1; i<=1000000; i++)
	{
		str = {
		Name:"HongGilDong",
		Mobile:"010-123-4567",
		"E-Mail":"ysoftman@naver.com",
		Clan:"Best_of_Best",
		Inventory:{
			Sword:"HighLevel",
			Robe:"MediumLevel",
			Potions:{
				HP_Potion:"SmallSize",
				MP_Potion:"BigSize"
				},
			PortalScroll:"1"
			},
		Status:{
			HP:i,
			MP:i
			},
		Skill:{
			FireBall:"1",
			Blizzard:"2"
			}
		}
		
		db.col1.save(str);
	}
	return 1;
}
db.eval(test2);

# memory dependent �ϱ� ������ page fault �� �߻����� ���� ������ �޸𸮰� ���� ��츦 ����
# 100������ index ��� ���� 1�ʳ� �˻� �Ϸ�
# 1000������ index ��� ���� �� 2�� �ҿ�, index ���� 1�ʳ�
# Status.HP �� 123 �ΰ� 
db.col1.find({"Status.HP":123}).count()

# Status.HP �� 1 ���� ū��
# 100������ index ��� ���� 1�ʳ� �˻� �Ϸ�
# 1000������ index ��� ���� �� 2�� �ҿ�, index ���� 1�ʳ�
db.col1.find({"Status.HP":{$gt:1}}).count()

# Status.HP �� 1 ���� ������
# 100������ index ��� ���� 1�ʳ� �˻� �Ϸ�
# 1000������ index ��� ���� �� 2�� �ҿ�, index ���� 1�ʳ�
db.col1.find({"Status.HP":{$lt:1000000}}).count()

# Status.HP �� 1 ���� ū�ų� ������
db.col1.find({"Status.HP":{$gte:1}}).count()

# Status.HP �� 1 ���� �۰ų� ������
db.col1.find({"Status.HP":{$gte:1}}).count()
*/

//////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Mongo Client Test (Java)
// mongo-java-driver-2.9.3.jar ���
//////////////////////////////////////////////////////////////////////////////////
import java.util.ArrayList;
import java.net.UnknownHostException;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.Mongo;
import com.mongodb.MongoException;


public class MongoDBTest
{	
	public static void main(String[] args )
	{
		InsertData("10.10.10.100", 10000, "testdb", "col1");
		//UpdateData("10.10.10.100", 10000, "testdb", "col1");
		//SearchData("10.10.10.100", 10000, "testdb", "col1");
	}
	
	public static void InsertData(String ip, int port, String dbname, String colname)
	{
		long timebefore = 0;
		long timeafter = 0;
		long timeresult = 0;
		
		timebefore = System.currentTimeMillis();
		try
		{
			// mongodb ����
			Mongo con = new Mongo(ip, port);

			// db ����ϱ�
			DB db = con.getDB(dbname);

			// collection ����ϱ�
			DBCollection collection = db.getCollection(colname);


			// ����ڵ鿡 ���ؼ�
			for (int i=1; i<=1000000; i++)
			{
				// document �� ������ ������ ����
				BasicDBObject doc = new BasicDBObject();
				// key, value ���� ������ �߰�
				doc.put("UserNo", i);
				// 100 ���� ��,���ھ� ����
				ArrayList<BasicDBObject> arraydata = new ArrayList<BasicDBObject>();
				for (int j=1; j<=100; j++)
				{
					BasicDBObject doc2 = new BasicDBObject("MapID", j);
					doc2.put("Score", j);
					arraydata.add(doc2);
				}
				doc.append("Map", arraydata);

				// ���� ������ ����
				collection.save(doc);

				// �����Ȳ �ľ��� ����
				if (i%1000 == 0)
				{
					System.out.println("Data Count:"+i);
				}
			}
		} 
		catch (UnknownHostException e)
		{
			e.printStackTrace();	
		}
		catch (MongoException e)
		{
			e.printStackTrace();
		}
		
		timeafter = System.currentTimeMillis();
		timeresult = (timeafter-timebefore)/1000;
		System.out.println("insert time: "+timeresult+"sec");
		
	}
	
	public static void UpdateData(String ip, int port, String dbname, String colname)
	{
		long timebefore = 0;
		long timeafter = 0;
		long timeresult = 0;
		
		timebefore = System.currentTimeMillis();
		try
		{
			// mongodb ����
			Mongo con = new Mongo(ip, port);

			// db ����ϱ�
			DB db = con.getDB(dbname);

			// collection ����ϱ�
			DBCollection collection = db.getCollection(colname);


			// ����ڵ鿡 ���ؼ�
			for (int i=1; i<=100000; i++)
			{
				BasicDBObject doc = new BasicDBObject();
				doc.put("UserNo", i);
				
				BasicDBObject doc2 = new BasicDBObject();
				doc2.append("$set", new BasicDBObject().append("Map.0.Score", 1234));
				
				// UserNo �� 555 �� ������� Map �迭�� ù��° MapID ���� 1234 �� �����ϱ�(���ǿ� �ش��ϴ� ������ ������ ��ť��Ʈ �ϳ��� �߰��ȴ�)
				// db.col1.update({"UserNo":555}, {$set:{"Map.0.MapID":1234}}, true);
				// ���� ������ ������Ʈ
				collection.update(doc, doc2, false, true);

				// �����Ȳ �ľ��� ����
				if (i%1000 == 0)
				{
					System.out.println("Data Count:"+i);
				}
			}
		} 
		catch (UnknownHostException e)
		{
			e.printStackTrace();	
		}
		catch (MongoException e)
		{
			e.printStackTrace();
		}
		
		timeafter = System.currentTimeMillis();
		timeresult = (timeafter-timebefore)/1000;
		System.out.println("update time: "+timeresult+"sec");
		
	}
	
	public static void SearchData(String ip, int port, String dbname, String colname)
	{
		long timebefore = 0;
		long timeafter = 0;
		long timeresult = 0;
		
		timebefore = System.currentTimeMillis();		
		try
		{
			// mongodb ����
			Mongo con = new Mongo(ip, port);

			// db ����ϱ�
			DB db = con.getDB(dbname);

			// collection ����ϱ�
			DBCollection collection = db.getCollection(colname);


			// ����ڵ鿡 ���ؼ�
			for (int i=1; i<=10000; i++)
			{
				BasicDBObject doc = new BasicDBObject();
				// ����� �Ѹ��� ��ü ������ �˻�
				doc.put("UserNo", i);
				// ����� �Ѹ��� Map.MaID == 10 �� �˻�
				//doc.put("Map.MapID", 55);
				DBCursor cursor = collection.find(doc);
				// ���� ��� �����ؼ� ��Ÿ����
				while (cursor.hasNext())
				{
					// �ӵ� ������ ���� �ַܼ� ������� �ʴ´�.
					//System.out.println(cursor.next());
					cursor.next();
				}
				// �����Ȳ �ľ��� ����
				if (i%1000 == 0)
				{
					System.out.println("Data Count:"+i);
				}
			}

		} 
		catch (UnknownHostException e)
		{
			e.printStackTrace();	
		}
		catch (MongoException e)
		{
			e.printStackTrace();
		}
		timeafter = System.currentTimeMillis();
		timeresult = (timeafter-timebefore)/1000;
		System.out.println("search time: "+timeresult+"sec");		
	}	
}



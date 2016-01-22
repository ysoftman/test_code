package com.Android_ServerMon;

import com.Android_ServerMon.R;

import android.os.Bundle;
import android.app.Activity;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.view.View.OnClickListener; // ���� Ŭ�� ������ ����� ����


public class MainActivity extends Activity {
	
	public static int THREADCNT = 4;
	public static int REQUEST_CNT = 1000;
	
	public static long memberno1 = 4105000000127825L;
	public static long memberno2 = 4105000000062365L;
	public static long memberno3 = 88899626759571853L;
	public static long memberno4 = 88899626759576869L;
	
	public String[] strResult = new String[1];
	
	// ������
	public class WorkerThread extends Thread {
		public int threadNo;
		public int cnt = 0;
		long memberno;
		
		public WorkerThread(int threadNo) {
			this.threadNo = threadNo;
			switch (threadNo) {
				case 0:
					memberno = memberno1;
					break;
				case 1:
					memberno = memberno2;
					break;
				case 2:
					memberno = memberno3;
					break;
				case 3:
					memberno = memberno4;
					break;
				default:
					memberno = memberno1;
					break;
			}
		}
		
		public void run() {
			try {
				// ���� �����尡 �ƴ� �����忡���� UI �� ���� �� �� ���� �ּ�ó��
				// TextView tv = (TextView)findViewById(R.id.textView1);
				// HTTP �� ����� ���� ��û
				// BigInteger memberno = new BigInteger("4105000000102846");
				HttpExecutor http = new HttpExecutor("10.10.10.12", 10000, memberno);
				for (int i = 1; i <= REQUEST_CNT; i++) {
					cnt = i;					
					http.GetData("MobileOmok/XMapMemberInfo/", strResult);
					// Log.d("ysoftman", strResult[0]);
					
					// Thread.sleep(10);
				}
				
			} catch (Exception e) {
				Log.d("ysoftman", e.toString());
				e.printStackTrace();
			}
			
		}
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		// UI���ξ����忡�� ��Ʈ��ũ �۾��� �ȵ���̵� 3.0 ���� ����� �� ����
		// ��õ���� ������ ������ �ϰ� �ʹٸ�..
		// StrictMode.enableDefaults();
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		TextView tv = (TextView) findViewById(R.id.textView1);
		tv.setMaxLines(50);
		tv.setVerticalScrollBarEnabled(true);
		tv.setMovementMethod(new ScrollingMovementMethod());
		
		// ��ư ���ҽ� ���
		Button btn1 = (Button) findViewById(R.id.button1);
		btn1.setOnClickListener(m_ClickListener1);
		Button btn2 = (Button) findViewById(R.id.button2);
		btn2.setOnClickListener(m_ClickListener2);
		Button btn3 = (Button) findViewById(R.id.button3);
		btn3.setOnClickListener(m_ClickListener3);
				
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	// Ŭ��1 ������ ����
	private OnClickListener m_ClickListener1 = new OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated
			// method stub
			// �ؽ�Ʈ�� ���ҽ� ���
			TextView tv = (TextView) findViewById(R.id.textView1);
			tv.scrollTo(0, 0);
			tv.setText("Button1 Clicked\n");
			
			WorkerThread nwThread = new WorkerThread(1);
			nwThread.start();
			
			// System.nanoTime();
			long lStartTime = System.currentTimeMillis();
			
			// Log.d("ysoftman", "nwThread.isAlive() : " + nwThread.isAlive());
			try {
				nwThread.join();
			} catch (Exception e) {
				e.printStackTrace();
			}
			// Log.d("ysoftman", "nwThread.isAlive() : " + nwThread.isAlive());

			String strMsg = "";
			//for (int i = 0; i < THREADCNT; i++)
			{
				strMsg += "Thread --> " + nwThread.cnt + " / " + REQUEST_CNT + "\n";
				// Log.d("ysoftman", strMsg);
				int scrollamout = tv.getLayout().getLineTop(tv.getLineCount()) - tv.getHeight();
				if (scrollamout > tv.getHeight()) {
					tv.scrollTo(0, scrollamout);
				}
			}			
			tv.append(strMsg);
			
			long lEndTime = System.currentTimeMillis();
			String strElapsedTime = "\n\nElapsedTime: " + (lEndTime - lStartTime) + "ms";
			
			if (strResult[0] == null) {
				strResult[0] = "Response... none";
			}
			tv.append(strResult[0]);
			tv.append("\n\nJust one thread used...");
			tv.append(strElapsedTime);
			int scrollamout = tv.getLayout().getLineTop(tv.getLineCount()) - tv.getHeight();
			if (scrollamout > tv.getHeight()) {
				tv.scrollTo(0, scrollamout);
			}
			
		}
	};
	
	// Ŭ��2 ������ ����
	private OnClickListener m_ClickListener2 = new OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated
			// method stub
			TextView tv = (TextView) findViewById(R.id.textView1);
			tv.setText("Button2 Clicked\n");
			
			WorkerThread myThread[] = new WorkerThread[THREADCNT];
			for (int i = 0; i < THREADCNT; i++) {
				myThread[i] = new WorkerThread(i);
				myThread[i].start();
			}
			
			long lStartTime = System.currentTimeMillis();
			try {
				
				while (true) {
					String strMsg = "";
					boolean bEnd = true;
					for (int i = 0; i < THREADCNT; i++) {
						if (myThread[i].getState() == Thread.State.TERMINATED) {
							bEnd = bEnd && true;
						} else {
							bEnd = false;
						}
					}
					for (int i = 0; i < THREADCNT; i++) {
						strMsg += "Thread[" + i + "] --> " + myThread[i].cnt + " / " + REQUEST_CNT + "\n";
						// Log.d("ysoftman", strMsg);
						int scrollamout = tv.getLayout().getLineTop(tv.getLineCount()) - tv.getHeight();
						if (scrollamout > tv.getHeight()) {
							tv.scrollTo(0, scrollamout);
						}
					}
					// Thread.sleep(10);
					
					if (bEnd) {
						tv.setText(strMsg);
						
						long lEndTime = System.currentTimeMillis();
						String strElapsedTime = "\n\nElapsedTime: " + (lEndTime - lStartTime) + "ms";
						
						strMsg = "All Threads Terminated\n";
						tv.append(strMsg);
						tv.append(strElapsedTime);
						tv.scrollTo(0, tv.getLayout().getLineTop(100));
						break;
					}
					
				}
			} catch (Exception e) {
				e.printStackTrace();
			}

		}
	};
	
	
	
	// Ŭ��3 ������ ����
	private OnClickListener m_ClickListener3 = new OnClickListener() {
		@Override
		public void onClick(View v) {
			// TODO Auto-generated
			// method stub
			TextView tv = (TextView) findViewById(R.id.textView1);
			tv.setText("Button3 Clicked\n");
			
			try {
				// NDKManager ����ϱ�
				JNIManager jni = new JNIManager();
				jni.Print();
				int c = jni.Add(1, 2);
				Log.d("ysoftman", "jni.Add(1,2) retun " + c);
				tv.append("jni.Add(1,2) retun " + c + "\n");
				String msg = jni.PrintString("YoonByoungHoon");
				Log.d("ysoftman", "jni.PrintString(\"YoonByoungHoon\") retun " + msg + "\n");
				tv.append("jni.PrintString(\"YoonByoungHoon\") retun " + msg + "\n");
			} catch (Exception e) {
				e.printStackTrace();
			}

		}
	};	
}

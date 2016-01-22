package com.Android_ServerMon;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

import android.util.Log;


/**
 *	@brief							송신/수신을 담당하는 세션 클래스
 *	@author							윤병훈
 *	@param							None
 *	@return							None
 */	
public class Session
{	
	Socket m_sc = null;

	/**
	 *	@brief							소켓을 생성하여 주어진 호스트에 연결
	 *	@author							윤병훈
	 *	@param			ip				Server ip
	 *	@param			port			Server port
	 *	@return							성공하면 0 리턴
	 */	
	public int Connect(String ip, int port)
	{
		try
		{
			m_sc = new Socket(ip, port);
			// linger time 을 0 으로 하여 closed socket 이 TIME_WAIT 상태에 빠지지 않도록 한다.
			// 실제 배포시 아래 linger 함수를 사용하지 않도록 한다.(QA나 기타 성능테스트시에만 사용)
			//m_sc.setSoLinger(true, 0);
			return 0;
		}
		catch (Exception e)
		{
			String errmsg = "Error : " + e.toString();
			System.out.println(errmsg);
			return -1;
		}
	}

	/**
	 *	@brief							생성된 소켓을 이용하여 메시시 송신
	 *	@author							윤병훈
	 *	@param			bytes			송신할 값(바이트)
	 *	@return							성공하면 0 리턴
	 */	
	public int Send(byte[] bytes)
	{
		try
		{
			// 송신버퍼(텍스트 스트림) 생성, 소켓의 getOutputStream 에 연결하여 사용
			//PrintWriter writer = new PrintWriter(m_sc.getOutputStream(), true);
			// 메시지 전송
			//writer.print(msg);

			// 송신버퍼(바이트 스트림) 생성, 소켓의 getOutputStream 에 연결하여 사용
			OutputStream writer = m_sc.getOutputStream();
			// 메시지 전송
			// writeBytes 는 String(글자당 2바이트) 을 취급한다.
			//writer.writeBytes(msg);
			// write 는 바이트 단위로 처리한다.
			writer.write(bytes);

			return 0;
		}
		catch (Exception e)
		{
			String errmsg = "Error : " + e.toString();
			System.out.println(errmsg);
			e.printStackTrace();
			return -1;
		}
	}

	/**
	 *	@brief							생성된 소켓을 이용하여 메시지 수신
	 *	@author							윤병훈
	 *	@param			timeout			타임아웃 값(ms)
	 *	@return							수신된 값(문자열)
	 */		
	public String Receive(int timeout)
	{
		byte[] buffer = null;
		int received = 0;
		int current_received = 0;
		int basesize = 4096;
		InputStream is = null;
		String strRecv = "";
		
		try
		{
			// Receive 타임아웃 (milliseconds)
			m_sc.setSoTimeout(timeout);

			// 수신버퍼(바이트 스트림) 생성, 소켓의 getInputStream 에 연결하여 사용
			is = m_sc.getInputStream();
			buffer = new byte[basesize];
			while (received < basesize)
			{
				// read() 함수는 더이상 읽을 데이터가 없으면 -1를 리턴한다.
				// 서버쪽에서 close 하지 않으면 데이터를 다 받더라도 링크가 지속된다.
				// 때문에 수신해야될 데이터가 더 있다고 판단하게 되고 결국 타임아웃 예외가 발생한다.
				current_received = is.read(buffer, received, basesize - received);
								
				// 읽어야 하는데도 available 리턴 값이 0 이 될 수 있다
				// Returns an estimated number of bytes that can be read or skipped without blocking for more input
				// this method provides such a weak guarantee that it is not very useful in practice. 
				//int availnum = is.available();
				
				//Log.d("ysoftman", "received : " + received);
				// 읽을 데이터가 없으면
				if (current_received == -1)
				{
					break;
				}
				
				received += current_received;
			}
		}
		catch (Exception e)
		{
			String errmsg = "Error : " + e.toString();
			System.out.println(errmsg);
			Log.d("ysoftman", errmsg);
			e.printStackTrace();
			return null;
		}


		// 문자열로 변환
		try
		{
			strRecv += new String(buffer, "utf-8");
			return strRecv;
		}
		catch (Exception e)
		{
			System.out.println("Error : " + e.toString());
			e.printStackTrace();
			return null;
		}
				
//		// http 의 Content-Length 값 파싱하기
//		int start_idx = temp.indexOf("Content-Length: ");
//		start_idx += "Content-Length: ".length();
//		int end_idx = temp.indexOf("\r\n", start_idx);
//		String lengthstring = temp.substring(start_idx, end_idx);
//		int length = Integer.parseInt(lengthstring);
	}

	/**
	 *	@brief							소켓 연결 닫기
	 *	@author							윤병훈
	 *	@param							None
	 *	@return							None
	 */		
	public void Disconnect()
	{
		try
		{
			m_sc.close();
			//System.out.println("Socket Closed");
		}
		catch (Exception e)
		{
			System.out.println("Socket Close Error : " + e.toString());
			e.printStackTrace();
		}
	}

	/**
	 *	@brief							주어진 호스트(str)에 대한 IP 얻어오기
	 *	@author							윤병훈
	 *	@param			str				호스트 이름
	 *	@return							host ip 를 문자열로 리턴
	 */
	public String getIP(String str)
	{
		try
		{
			InetAddress addr = InetAddress.getByName(str);
			// 호스트이름/ip
			//System.out.println("IP : " + addr.toString());
			// 호스트
			//System.out.println("IP : " + addr.getHostName());
			// ip
			//System.out.println("IP : " + addr.getHostAddress());
			return addr.getHostAddress();
		}
		catch (Exception e)
		{
			System.out.println("Error : " + e.toString());
			e.printStackTrace();
			return null;
		}
	}	
}

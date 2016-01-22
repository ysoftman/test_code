package com.Android_ServerMon;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

import android.util.Log;


/**
 *	@brief							�۽�/������ ����ϴ� ���� Ŭ����
 *	@author							������
 *	@param							None
 *	@return							None
 */	
public class Session
{	
	Socket m_sc = null;

	/**
	 *	@brief							������ �����Ͽ� �־��� ȣ��Ʈ�� ����
	 *	@author							������
	 *	@param			ip				Server ip
	 *	@param			port			Server port
	 *	@return							�����ϸ� 0 ����
	 */	
	public int Connect(String ip, int port)
	{
		try
		{
			m_sc = new Socket(ip, port);
			// linger time �� 0 ���� �Ͽ� closed socket �� TIME_WAIT ���¿� ������ �ʵ��� �Ѵ�.
			// ���� ������ �Ʒ� linger �Լ��� ������� �ʵ��� �Ѵ�.(QA�� ��Ÿ �����׽�Ʈ�ÿ��� ���)
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
	 *	@brief							������ ������ �̿��Ͽ� �޽ý� �۽�
	 *	@author							������
	 *	@param			bytes			�۽��� ��(����Ʈ)
	 *	@return							�����ϸ� 0 ����
	 */	
	public int Send(byte[] bytes)
	{
		try
		{
			// �۽Ź���(�ؽ�Ʈ ��Ʈ��) ����, ������ getOutputStream �� �����Ͽ� ���
			//PrintWriter writer = new PrintWriter(m_sc.getOutputStream(), true);
			// �޽��� ����
			//writer.print(msg);

			// �۽Ź���(����Ʈ ��Ʈ��) ����, ������ getOutputStream �� �����Ͽ� ���
			OutputStream writer = m_sc.getOutputStream();
			// �޽��� ����
			// writeBytes �� String(���ڴ� 2����Ʈ) �� ����Ѵ�.
			//writer.writeBytes(msg);
			// write �� ����Ʈ ������ ó���Ѵ�.
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
	 *	@brief							������ ������ �̿��Ͽ� �޽��� ����
	 *	@author							������
	 *	@param			timeout			Ÿ�Ӿƿ� ��(ms)
	 *	@return							���ŵ� ��(���ڿ�)
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
			// Receive Ÿ�Ӿƿ� (milliseconds)
			m_sc.setSoTimeout(timeout);

			// ���Ź���(����Ʈ ��Ʈ��) ����, ������ getInputStream �� �����Ͽ� ���
			is = m_sc.getInputStream();
			buffer = new byte[basesize];
			while (received < basesize)
			{
				// read() �Լ��� ���̻� ���� �����Ͱ� ������ -1�� �����Ѵ�.
				// �����ʿ��� close ���� ������ �����͸� �� �޴��� ��ũ�� ���ӵȴ�.
				// ������ �����ؾߵ� �����Ͱ� �� �ִٰ� �Ǵ��ϰ� �ǰ� �ᱹ Ÿ�Ӿƿ� ���ܰ� �߻��Ѵ�.
				current_received = is.read(buffer, received, basesize - received);
								
				// �о�� �ϴµ��� available ���� ���� 0 �� �� �� �ִ�
				// Returns an estimated number of bytes that can be read or skipped without blocking for more input
				// this method provides such a weak guarantee that it is not very useful in practice. 
				//int availnum = is.available();
				
				//Log.d("ysoftman", "received : " + received);
				// ���� �����Ͱ� ������
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


		// ���ڿ��� ��ȯ
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
				
//		// http �� Content-Length �� �Ľ��ϱ�
//		int start_idx = temp.indexOf("Content-Length: ");
//		start_idx += "Content-Length: ".length();
//		int end_idx = temp.indexOf("\r\n", start_idx);
//		String lengthstring = temp.substring(start_idx, end_idx);
//		int length = Integer.parseInt(lengthstring);
	}

	/**
	 *	@brief							���� ���� �ݱ�
	 *	@author							������
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
	 *	@brief							�־��� ȣ��Ʈ(str)�� ���� IP ������
	 *	@author							������
	 *	@param			str				ȣ��Ʈ �̸�
	 *	@return							host ip �� ���ڿ��� ����
	 */
	public String getIP(String str)
	{
		try
		{
			InetAddress addr = InetAddress.getByName(str);
			// ȣ��Ʈ�̸�/ip
			//System.out.println("IP : " + addr.toString());
			// ȣ��Ʈ
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

////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Robocode �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
import java.awt.Color;
import robocode.*;

public class RobocodeTest extends Robot
{
	public void run()
	{
		setBodyColor(Color.blue);	// ��ũ ����
		setGunColor(Color.red);		// ���� ����
		setBulletColor(Color.red);	// ������ ����
		
		while (true)
		{
			turnGunRight(360);	// ���� ���������� 360�� ȸ��
		}
	}
	// ���� �߰ߵǸ�
	public void onScannedRobot(ScannedRobotEvent e)
	{
		// �Ÿ��� ª���� ���ϰ� �߻�
		if (e.getDistance() < 20)
		{
			fire(3);
		}
		else
		{
			fire(1);
		}
	}
	// �츮�� ���� ������
	public void onHitByBullet(HitByBulletEvent e) 
	{
		turnLeft(90);		// ��ũ ���� 90���� ����
		ahead(100);			// ��ũ ����
	}
}

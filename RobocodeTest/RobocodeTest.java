////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Robocode 테스트
////////////////////////////////////////////////////////////////////////////////////
import java.awt.Color;
import robocode.*;

public class RobocodeTest extends Robot
{
	public void run()
	{
		setBodyColor(Color.blue);	// 탱크 색상
		setGunColor(Color.red);		// 대포 색상
		setBulletColor(Color.red);	// 대포알 색상
		
		while (true)
		{
			turnGunRight(360);	// 대포 오른쪽으로 360도 회전
		}
	}
	// 적을 발견되면
	public void onScannedRobot(ScannedRobotEvent e)
	{
		// 거리가 짧으면 강하게 발사
		if (e.getDistance() < 20)
		{
			fire(3);
		}
		else
		{
			fire(1);
		}
	}
	// 우리가 포를 맞으면
	public void onHitByBullet(HitByBulletEvent e) 
	{
		turnLeft(90);		// 탱크 왼쪽 90도로 꺽기
		ahead(100);			// 탱크 전진
	}
}

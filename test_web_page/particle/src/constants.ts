// 공유 상수 — 게임 전반의 색상/물리/게임플레이 튜닝 값.

// 엔티티 색상 (종류별로 시각적으로 구분)
export const COLORS = {
  background: 0x0b0e1a,
  ship: 0x4df3ff, // 시안색 삼각형
  shipThrust: 0xff9f43, // 엔진 화염
  bullet: 0xffe74c, // 노란 점
  rockLevels: [0xc06bff, 0xff6b9e, 0xff9f43, 0x9aa7b8] as const, // index = sizeLevel (0 최소 .. 3 최대)
  dust: 0xfff3c4,
  hudText: 0xdfe7ef,
} as const;

// Matter.js 충돌 카테고리 (비트마스크)
export const COLLISION = {
  ship: 0x0001,
  bullet: 0x0002,
  rock: 0x0004,
} as const;

// 게임플레이 튜닝
export const SHIP = {
  size: 18, // 삼각형 절반 길이
  thrustForce: 0.0006,
  turnSpeed: 0.065, // 60fps 기준 프레임당 회전(rad)
  frictionAir: 0.02,
  fireCooldownMs: 160,
  invulnerableMs: 1500,
} as const;

export const BULLET = {
  radius: 2.5,
  speed: 11,
  lifeMs: 1100,
  frictionAir: 0,
} as const;

export const ROCK = {
  maxLevel: 3, // 최초 스폰 레벨; 피격 시 level-1 의 작은 바위들로 분열
  splitCount: 3, // 피격당 분열 조각 수 (n)
  baseRadius: 14, // 레벨 0 반지름; 반지름 = baseRadius * (1.7 ** level)
  radiusJitter: 0.25, // 폴리곤 꼭짓점 반지름 지터 비율
  vertexCount: { min: 7, max: 11 },
  frictionAir: 0,
  restitution: 0.9,
  splitImpulse: 2.2, // 분열 조각에 가산되는 방사형 속도
  maxSpeed: 6,
  initialCount: 4, // 웨이브 시작 시 바위 수
} as const;

export const DUST = {
  countSmall: 8, // 바위 분열 시 먼지 개수
  countFinal: 22, // 바위 최종 소멸 시 먼지 개수
  lifeMs: 700,
  speed: 3.5,
} as const;

export const SCORE_PER_LEVEL = [100, 50, 20, 10] as const; // index = 파괴된 바위의 sizeLevel

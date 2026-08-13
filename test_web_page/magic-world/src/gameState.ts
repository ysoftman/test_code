export interface PlayerState {
  name: string;
  hp: number;
  maxHp: number;
  mp: number;
  maxMp: number;
  atk: number;
  def: number;
}

export const GameState = {
  player: {
    name: "HERO",
    hp: 30,
    maxHp: 30,
    mp: 10,
    maxMp: 10,
    atk: 6,
    def: 2,
  } as PlayerState,
  gold: 0,
  battles: 0,
  reset(): void {
    this.player.hp = this.player.maxHp;
    this.player.mp = this.player.maxMp;
    this.gold = 0;
    this.battles = 0;
  },
};

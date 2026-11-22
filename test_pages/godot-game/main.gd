extends Node2D

const W := 480.0
const H := 720.0
const PLAYER_Y := H - 70.0
const PLAYER_R := 14.0
const SPEED := 380.0

var player_x := W / 2
var rocks: Array[Dictionary] = []
var stars: Array[Vector2] = []
var spawn_t := 0.0
var score := 0.0
var best := 0.0
var over := false
var font := ThemeDB.fallback_font


func _ready() -> void:
	for i in 60:
		stars.append(Vector2(randf() * W, randf() * H))


func _process(delta: float) -> void:
	for i in stars.size():
		stars[i].y = fmod(stars[i].y + 40.0 * delta, H)
	queue_redraw()
	if over:
		return

	score += delta
	var dir := Input.get_axis("ui_left", "ui_right")
	dir += float(Input.is_physical_key_pressed(KEY_D)) - float(Input.is_physical_key_pressed(KEY_A))
	player_x += clampf(dir, -1, 1) * SPEED * delta
	# 마우스/터치(터치는 기본으로 마우스 이벤트로 에뮬레이트됨) 누르고 있으면 그 x 로 따라감
	if Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT):
		player_x = move_toward(player_x, get_local_mouse_position().x, SPEED * 1.5 * delta)
	player_x = clampf(player_x, PLAYER_R, W - PLAYER_R)

	# 시간이 지날수록 더 자주, 더 빠르게 떨어진다
	spawn_t -= delta
	if spawn_t <= 0:
		spawn_t = maxf(0.12, 0.7 - score * 0.015)
		var r := randf_range(10, 28)
		rocks.append({"p": Vector2(randf() * W, -r), "r": r, "v": 180 + score * 8 + randf() * 120})

	var player := Vector2(player_x, PLAYER_Y)
	for rock in rocks:
		rock.p.y += rock.v * delta
		if rock.p.distance_to(player) < rock.r + PLAYER_R * 0.7:
			over = true
			best = maxf(best, score)
	rocks = rocks.filter(func(rock): return rock.p.y < H + rock.r)


func _unhandled_input(event: InputEvent) -> void:
	var restart := (
		event.is_action_pressed("ui_accept")
		or (event is InputEventMouseButton and event.is_pressed())
	)
	if over and restart:
		rocks.clear()
		score = 0
		spawn_t = 0
		player_x = W / 2
		over = false


func _draw() -> void:
	for s in stars:
		draw_circle(s, 1.2, Color(1, 1, 1, 0.35))
	for rock in rocks:
		draw_circle(rock.p, rock.r, Color("e07a5f"))
		draw_circle(rock.p - Vector2(rock.r, rock.r) * 0.3, rock.r * 0.3, Color("f2a88f"))

	var ship := Color("ff5d5d") if over else Color("6ea8fe")
	draw_colored_polygon(
		PackedVector2Array(
			[
				Vector2(player_x, PLAYER_Y - PLAYER_R * 1.4),
				Vector2(player_x + PLAYER_R, PLAYER_Y + PLAYER_R),
				Vector2(player_x - PLAYER_R, PLAYER_Y + PLAYER_R),
			]
		),
		ship
	)

	draw_string(font, Vector2(16, 40), "%.1f" % score, HORIZONTAL_ALIGNMENT_LEFT, -1, 28)
	draw_string(
		font,
		Vector2(0, 40),
		"BEST %.1f  " % best,
		HORIZONTAL_ALIGNMENT_RIGHT,
		W,
		18,
		Color(1, 1, 1, 0.6)
	)
	if over:
		draw_string(font, Vector2(0, H / 2 - 20), "GAME OVER", HORIZONTAL_ALIGNMENT_CENTER, W, 44)
		draw_string(
			font,
			Vector2(0, H / 2 + 24),
			"Space / Click to restart",
			HORIZONTAL_ALIGNMENT_CENTER,
			W,
			20,
			Color(1, 1, 1, 0.7)
		)
	elif score < 3:
		draw_string(
			font,
			Vector2(0, H / 2),
			"Arrows / A D / Drag to dodge",
			HORIZONTAL_ALIGNMENT_CENTER,
			W,
			20,
			Color(1, 1, 1, 0.7)
		)

val count = sc.parallelize(1 to 100).filter { _ =>
    val x = math.random
    val y = math.random
    x*x + y*y < 1
}.count()
println(s"Pi is roughly ${4.0 * count / 100}")
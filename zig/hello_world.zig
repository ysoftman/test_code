// zig run hello_world.zig
const std = @import("std");
pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    try stdout.print("hello, {s}!\n", .{"world"});
}

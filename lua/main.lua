function main()
	print("Hello from lua!")
	pencolor(0x00ff00ff)
	line(10, 40, 200, 100)
	pencolor(0xff0000ff)
	line(10, 100, 200, 40)
	text(50, 50, "Hello, World!", 0xffff00ff)
	flip()
	delay(2000)
end

main()
print("goodbye lua.")

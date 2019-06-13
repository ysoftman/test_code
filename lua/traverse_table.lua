mydata = {
    lemon = {
        price = 100,
        market = "aaa",
    },
    orange = {
        price = 150,
        market = "bbb",
    }    
}

for k1, v1 in pairs(mydata) do
    print ("".. k1, v1)

    if type(v1) == "table" then
        for k2, v2 in pairs(v1) do
            print ("\t".. k2, v2)

            if type(v2) == "table" then
                for k3, v3 in pairs(v2) do
                    print ("\t\t".. k3, v3)
                end
            end
        end
    end
end
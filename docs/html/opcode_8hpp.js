var opcode_8hpp =
[
    [ "Opcode", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04", [
      [ "POP", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04aefdb39a4c7286afcecf0e8a7435fce6a", null ],
      [ "PEEK", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a422982ae154d01bf45c66c601981e6c2", null ],
      [ "POKE", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04af0e166c6fa2443a133f77d263161b11f", null ],
      [ "COPY", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04ae8606d021da140a92c7eba8d9b8af84f", null ],
      [ "JMP", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a152b9af76a9e7dd95d9da277b69fdd95", null ],
      [ "JMPF", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a13c24ba31a2f9be1455950325eadcae6", null ],
      [ "JMPF_POP", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a58d52e0bb8076b5b59f991df9f515adc", null ],
      [ "JMPT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04ab123f83cf8bbdc76dfa6b3436b372e60", null ],
      [ "JMPT_POP", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04aea6c3089d9a0be7fcc7b17686910361d", null ],
      [ "NULLVAL", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04ad4184f26935a3ca6e6704e32771f53be", null ],
      [ "INTEGER", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a5d5cd46919fa987731fb2edefe0f2a0c", null ],
      [ "FLOAT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04ae738c26bf4ce1037fa81b039a915cbf6", null ],
      [ "BOOLEAN", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04ac48d5da12d702e73d6966069f2687376", null ],
      [ "STRING", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a63b588d5559f64f89a416e656880b949", null ],
      [ "ARRAY", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04acb4fb1757fb37c43cded35d3eb857c43", null ],
      [ "FUNCTION", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a6a72a6a776662a244f82d31e9274a07b", null ],
      [ "ASSIGNINDEX", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04ad841b7b2c8fba802dc3425c697d2ee11", null ],
      [ "ADD", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a9eeb52badb613229884838847294b90d", null ],
      [ "SUBTRACT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a23ebcc4776b613af25dfbe7c8ce4813e", null ],
      [ "MULTIPLY", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a080aaf8d817ada96fca7096b7b55bd30", null ],
      [ "DIVIDE", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a210c66d794cec40488f3f8f634d6c33b", null ],
      [ "MODULO", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a928ab45d616dde447dbbbd0270db87ad", null ],
      [ "NEGATIVE", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a50546bf973283065b6ccf09faf7a580a", null ],
      [ "NOT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a10df3d67626099df882920ba6552f16d", null ],
      [ "LT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04ac562607189d77eb9dfb707464c1e7b0b", null ],
      [ "LTE", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04acc981ecc65ecf63ad1673cbec9c64198", null ],
      [ "GT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04acd6a9bd2a175104eed40f0d33a8b4020", null ],
      [ "GTE", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a32d35312e8f24bc1669bd2b45c00d47c", null ],
      [ "EQ", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a2dcbad7477fd40561e8b8198f173bd47", null ],
      [ "NEQ", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a375b332cf2e0c6d522baf007ef7cb554", null ],
      [ "INDEX", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04acb4ae3b37047fb4b2c0d16f8bf84f076", null ],
      [ "SLICE", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a0a1031e189c0c5e08d55c44fc02a4b26", null ],
      [ "GETITERATOR", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a007663613f231d7bfcee9025e2d9f756", null ],
      [ "ITERATORNEXT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a0025221d3192b323ba93e40e7c1403fb", null ],
      [ "ISITERATOREND", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04ae7185531b0fe3cf42b93676198c7af37", null ],
      [ "CASTINTEGER", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a0a109fb07a3a6984f50ffe52dd2c213b", null ],
      [ "CASTFLOAT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04af721c36554a56d3695dda4af2863efbb", null ],
      [ "CASTBOOLEAN", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a958f96740eee65afc3776e66d48a5620", null ],
      [ "CALLFUNC", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04a8fbd21f6a619e33ff038cdf5a69a14d8", null ],
      [ "RETURN", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04aa2bec276a54439fe011eb523b845dac5", null ],
      [ "PRINT", "opcode_8hpp.html#a3db69378da7fea0383c531f8cae78f04af96eee4e48ee90430f17fb3a8388507b", null ]
    ] ]
];
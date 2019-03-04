import kmerDecoder as KD

seq = "ATGAGGGGGATGCCCCTCTTTGAGCCCAAGGACGTAGCCTATATTTTGCAACGCGTGAC"


"""
--------------------------------------------------------
                        Kmers
--------------------------------------------------------
"""
print("Kmers\n")

kmers_q = KD.strQueue()
kmers_params = KD.IntVector([27])  # params = {k}

kmers = KD.InputModuleDefault()
kmers.setParms(kmers_params)
kmers.getKmers(kmers_q, seq)

for i in range(kmers_q.size()):
    print ("{}: {}".format(i+1, kmers_q.front()))
    kmers_q.pop()


"""
--------------------------------------------------------
                        Skipmers
--------------------------------------------------------
"""
print("\nSkipmers\n")

skipmers_q = KD.strQueue()
skipmers_params = KD.IntVector([3, 4, 27])  # params = {m, n, k}

skipmers = KD.InputModuleSkipmers()
skipmers.setParms(skipmers_params)
skipmers.getKmers(skipmers_q, seq)

for i in range(skipmers_q.size()):
    print ("{}: {}".format(i+1, skipmers_q.front()))
    skipmers_q.pop()

"""
--------------------------------------------------------
                        Minimizers
--------------------------------------------------------
"""
print("\nMinimizers\n")

minimizers_q = KD.strQueue()
minimizers_params = KD.IntVector([5, 10])  # params = {k, w}

minimizers = KD.InputModuleMinimzers()
minimizers.setParms(minimizers_params)
minimizers.getKmers(minimizers_q, seq)

for i in range(minimizers_q.size()):
    print ("{}: {}".format(i+1, minimizers_q.front()))
    minimizers_q.pop()

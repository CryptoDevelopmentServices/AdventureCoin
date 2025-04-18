// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2018 AdventureCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <hash.h>
#include <tinyformat.h>
#include <utilstrencodings.h>
#include <crypto/common.h>
#include <versionbits.h>
#include <consensus/params.h>
#include <chainparams.h>
#include <adventurecoin.h>

uint256 CBlockHeader::GetIndexHash(int nHeight) const
{
    // Activate blake2b indexing
    const Consensus::Params& consensusParams = Params().GetConsensus();
    if (nHeight >= consensusParams.blakeIndexing) {
        return Blake2b(BEGIN(nVersion), END(nNonce));
    } else {
        return GetWorkHash(consensusParams, nHeight);
    }
}

uint256 CBlockHeader::GetWorkHash(const Consensus::Params& consensusParams, int nHeight) const
{
    if (nHeight >= consensusParams.rainforestHeightV2) {
        return RainforestV2(BEGIN(nVersion), END(nNonce));
    } else if (nHeight >= consensusParams.rainforestHeight && nHeight < consensusParams.rainforestHeightV2) {
        return Rainforest(BEGIN(nVersion), END(nNonce));
    } else if (nHeight > consensusParams.advcHeight && nHeight < consensusParams.rainforestHeight) {
        return Groestl(BEGIN(nVersion), END(nNonce));
    } else {
        return SerializeHash(*this);
    }
}

uint256 CBlockHeader::GetWorkHash(int nHeight, int nIndex) const
{
    if (nIndex > 0) { std::cout << "\n\nHeight: " << nHeight << ", nIndex: " << nIndex << "\n"; }
    const Consensus::Params& consensusParams = Params().GetConsensus();
    return GetWorkHash(consensusParams, nHeight);
}

std::string CBlock::ToString(int nHeight) const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetIndexHash(nHeight).ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}

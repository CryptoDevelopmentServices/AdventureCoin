// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>
#include <memory>

#include <chainparamsseeds.h>

#include "arith_uint256.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Let the quest begin";
    const CScript genesisOutputScript = CScript() << ParseHex("04c743587e4fce1f8913d1c36d197924a14a804a8db577c86bca007c91a5cab736c8fdf3e13087d1c6f324bdca8548fb2978733b62b2e6a05c5b9ff6b9f0ad0e") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 300000;
        consensus.BIP16Height = 0; // fixed
        consensus.BIP34Height = 6333;
        consensus.BIP34Hash = uint256S("0x4cf9771fec1f8c739172c5c9a3a39d8647aa731c4f055135dc3954ca514d0340"); // TODO: update with actual hash of block 6333
        consensus.BIP65Height = 6333;
        consensus.BIP66Height = 6333;
        consensus.powLimit = uint256S("0x3fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 180;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 75; 
        consensus.nMinerConfirmationWindow = 100; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1747404000;  // May 16, 2025 @ 14:00 UTC
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1778930000;    // May 8, 2033

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1747404000; // May 16, 2025 @ 14:00 UTC
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1778930000;   // Approx: May 16, 2026 @ 14:00 UTC


        // The best chain should have at least this much work.
		consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000180000"); // 5

        // By default assume that the signatures in ancestors of this block are valid.
		consensus.defaultAssumeValid = uint256S("0x0"); // 5

        // 10% of Block reward to operations wallet
        nDeveloperFee = 10;
 
        // This is the block height when the devfee starts working
        nDeveloperFeeStart = 1;
  
        // Developer wallet address
        strDeveloperFeeAddress = std::string("AeD4pPi3D5kB9aMEgH3eRHoD6XMKbrpRAW");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0x5a;
        pchMessageStart[2] = 0xeb;
        pchMessageStart[3] = 0x9f;
        nDefaultPort = 5403;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1745245284, 159840, 0x1e3fffff, 1, 300 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0xda4aaa17fd5f1c7db85cfebdb56e1b5d89739b9bf8c7a23c4cdf07a9649469a8"));
        assert(genesis.hashMerkleRoot == uint256S("0xe3c50fc5e5111951fb44d634a8907b732822e43466c519c4efa16717d92f3ce4"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they dont support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
	    vSeeds.emplace_back("seed.adventurecoin.quest");
        vSeeds.emplace_back("157.180.76.198"); // EU - NovaGrid	
        vSeeds.emplace_back("34.124.247.1"); // APAC - NovaGrid
        vSeeds.emplace_back("178.156.175.223"); // NA-EAST - NovaGrid
        vSeeds.emplace_back("5.78.108.16"); // NA-WEST - NovaGrid
        vSeeds.emplace_back("34.39.151.195"); // SA - NovaGrid	

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,10);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,123);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "advc";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0xda4aaa17fd5f1c7db85cfebdb56e1b5d89739b9bf8c7a23c4cdf07a9649469a8")},
                {5, uint256S("0xd7a52de54b9482af1ca65e2863a6e28a3af6caaeb28d71056aaa089e0fecf4a5")},
                {6333, uint256S("0x4cf9771fec1f8c739172c5c9a3a39d8647aa731c4f055135dc3954ca514d0340")},
                {30000, uint256S("0x9a58e6980e4f9b01f79131a4161ff57a869682d74c4c2ecd93f3af81433e37fd")},
                {60000, uint256S("0x690ffbb060c615c03cf108e8e053e3e727ec7c34499010d942e5c2d53fb200a2")},   
            }
        };


/*
HELP - calculate
genesis = 1507032223
1528276166-1507032223=21243943

839317/21243943=

*/

        chainTxData = ChainTxData{
            // Data as of block 00000017fb4512999352c3ae0a9ea0aa0fc03e8118f74d4ece68df939bb33d93 (height 60000).
            1757327963, // * UNIX timestamp of last known number of transactions
            839317,    // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.0395 // * 0.0750 -  estimated number of transactions per second after that timestamp
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 300000;
        consensus.BIP16Height = 0; // fixed
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00");
        consensus.BIP65Height = 12720;
        consensus.BIP66Height = 12720;
        consensus.powLimit = uint256S("0x3fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 180;
        //consensus.nZawyLwmaAveragingWindow = 90;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 5040; // 75%
        consensus.nMinerConfirmationWindow = 6720; // nPowTargetTimespan / nPowTargetSpacing / 2
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1517097600; // January 28, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1548633600; // January 28, 2019

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1517097600; // January 28, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1548633600; // January 28, 2019

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x95;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0xe4;
        pchMessageStart[3] = 0x95;
        nDefaultPort = 15403;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1745245225, 327904, 0x1e3fffff, 1, 300 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x733e2b71d472d605aa848689c2cd67cc9c0cff40760e863995d27809e5459bed"));
        assert(genesis.hashMerkleRoot == uint256S("0xe3c50fc5e5111951fb44d634a8907b732822e43466c519c4efa16717d92f3ce4"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        
        vSeeds.emplace_back("157.180.76.198");
        //vSeeds.emplace_back("seed.adventurecoin.org", false);
        //vSeeds.emplace_back("testnet-seed.adventurecoin.jp", false);
        

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,197);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tadvc";

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = {
            {
                {0, uint256S("0x733e2b71d472d605aa848689c2cd67cc9c0cff40760e863995d27809e5459bed")},
                
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Height = 0; // fixed
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("0x3fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 120;
        //consensus.nZawyLwmaAveragingWindow = 90;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0x5b;
        pchMessageStart[3] = 0xad;
        nDefaultPort = 25403;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1745245142, 8, 0x207fffff, 1, 300 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0xdaeb81fa9f89f990b8149786ded09b30982f4fd7ec8ea9600b01f3535c4a8238"));
        assert(genesis.hashMerkleRoot == uint256S("0xe3c50fc5e5111951fb44d634a8907b732822e43466c519c4efa16717d92f3ce4"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                {0, uint256S("0xdaeb81fa9f89f990b8149786ded09b30982f4fd7ec8ea9600b01f3535c4a8238")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,197);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "radvc";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2018-2020 The Sugarchain Yumekawa developers
// Copyright (c) 2025 The Crypto Development Services developers
// Copyright (c) 2025 The Adventurecoin developers
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

#include <arith_uint256.h> // DigiShieldZEC

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
    const char* pszTimestamp = "Let the Adventure begin";
    const CScript genesisOutputScript = CScript() << ParseHex("04ab719bc19fd2bcce5bf7dde93e8afe76722ca4eca2f3fb24394376e34c06463f21a6c3aea7d68681c5b415a6483902c4622b0b698ed152c4da75b5f89ca59557") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

// DigiShieldZEC
const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

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

        
        consensus.nSubsidyHalvingInterval = 1576800; // every 3 years

        consensus.BIP16Height = 0;  // always on
        consensus.BIP34Height = 17;
        consensus.BIP34Hash = uint256S("0x00"); // getblockhash 17
        consensus.BIP65Height = 0;  // always on
        consensus.BIP66Height = 0;  // always on
        consensus.powLimit = uint256S("003fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nPowTargetTimespan = 61200;

        consensus.nPowAllowMinDifficultyBlocksAfterHeight = boost::none; // DigiShieldZEC
        consensus.nPowAveragingWindow = 510; // DigiShieldZEC // 2550/nPowTargetSpacing(5) = 510
        assert(maxUint/UintToArith256(consensus.powLimit) == 1024); // DigiShieldZEC // 0x0000000000000000000000000000000000000000000000000000000000000400 == 1024
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow); // DigiShieldZEC // true: 1024 >= 510

        consensus.nPowMaxAdjustDown = 32; // DigiShieldZEC // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // DigiShieldZEC // 16% adjustment up
        consensus.nPowTargetSpacing = 60;

        consensus.fPowAllowMinDifficultyBlocks = false; // DigiShieldZEC
        consensus.fPowNoRetargeting = false; // DigiShieldZEC
        consensus.nRuleChangeActivationThreshold = 9180;
        consensus.nMinerConfirmationWindow = 12240;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113 are always on
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of SegWit (BIP141, BIP143, and BIP147) is always on
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        // TODO.ADVC.UPDATE
        // getblockhash 6513497 && "chainwork"
        consensus.nMinimumChainWork = uint256S("00000000000000000000000000000000000000000000000000003f23ef34da28");

        // By default assume that the signatures in ancestors of this block are valid.
        // TODO.ADVC.UPDATE
        // getblockhash 6513497 && "hash"
        consensus.defaultAssumeValid = uint256S("0x00");
          
        // 15% of Block reward to operations wallet
          nDeveloperFee = 10;
 
          // This is the block height when the devfee starts working
          nDeveloperFeeStart = 1;
  
          // Developer wallet address
          strDeveloperFeeAddress = "A5JsYYsjnbFYHDrpibAStTEGpxyZrPBVr3"; //Change this

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x9f;
        pchMessageStart[1] = 0xeb;
        pchMessageStart[2] = 0x4b;
        pchMessageStart[3] = 0x9d;
        nDefaultPort = 33230;
        nPruneAfterHeight = 100000;
        
        
        genesis = CreateGenesisBlock(1744221343, 353, 0x1f3fffff, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        
              
        assert(genesis.GetPoWHash() == uint256S("0x002a4688234301d87ba8a5e9b2d187ca893f892817c53d05a34a88889c0aea3f")); // genesis
        assert(consensus.hashGenesisBlock == uint256S("0xede8baba7b9828412b656c87fbe0dd2b4748a0499998b4f4c3b0dbd7811522b0")); // genesis
        assert(genesis.hashMerkleRoot == uint256S("0xe71dc16655132ebaf6b0a2897d676ebbd47d015649027f9c77b84aa33d44fb77"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they dont support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        // vSeeds.emplace_back("1seed.adventurecoin.info"); // cryptozeny
        // vSeeds.emplace_back("2seed.adventurecoin.info"); // cryptozeny
        // vSeeds.emplace_back("seed.adventurecoin.site"); // ROZ

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);  // legacy: starting with S (upper)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,125); // p2sh-segwit: starting with s (lower)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "advc";   // bech32: starting with advc1q

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0xede8baba7b9828412b656c87fbe0dd2b4748a0499998b4f4c3b0dbd7811522b0")},
            }
        };

        // TODO.ADVC.UPDATE
        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 855f0c66238bc0246c8ca25cf958283fd49b9fb4b217ddeb518e5ea9f5071b9e (6513497)
            /* nTime    */ 1744221343,
            /* nTxCount */ 1,
            /* dTxRate  */ 0.2053689306146399
        };
    }
};

/**
 * Testnet (v5)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";

        
        consensus.nSubsidyHalvingInterval = 1576800; // every 3 years

        consensus.BIP16Height = 0;  // always on
        consensus.BIP34Height = 17;
        consensus.BIP34Hash = uint256S("");   // TODO.ADVC
        consensus.BIP65Height = 0; // always on
        consensus.BIP66Height = 0; // always on
        consensus.powLimit = uint256S("003fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 61200;

        consensus.nPowAllowMinDifficultyBlocksAfterHeight = boost::none; // DigiShieldZEC
        consensus.nPowAveragingWindow = 510; // 2550 / nPowTargetSpacing(5) = 510

        assert(maxUint/UintToArith256(consensus.powLimit) == 1024); // DigiShieldZEC // 0x0000000000000000000000000000000000000000000000000000000000000400 == 1024
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow); // DigiShieldZEC // true: 1024 >= 510

        consensus.nPowMaxAdjustDown = 32; // DigiShieldZEC // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // DigiShieldZEC // 16% adjustment up

        consensus.nPowTargetSpacing = 60;

        consensus.fPowAllowMinDifficultyBlocks = false; // DigiShieldZEC
        consensus.fPowNoRetargeting = false; // DigiShieldZEC
        consensus.nRuleChangeActivationThreshold = 9180;
        consensus.nMinerConfirmationWindow = 12240;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113 are always on
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of SegWit (BIP141, BIP143, and BIP147) is always on
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        // TODO.ADVC.UPDATE
        // getblockhash 4000000 && "chainwork" (testnet)
        consensus.nMinimumChainWork = uint256S("000000000000000000000000000000000000000000000000000000014d9bf048");

        // By default assume that the signatures in ancestors of this block are valid.
        // TODO.ADVC.UPDATE
        // getblockhash 4000000 && "hash" (testnet)
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xb0;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0x90;
        pchMessageStart[3] = 0x70;
        nDefaultPort = 44229;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1744230279, 347, 0x1f3fffff, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

       

        assert(genesis.GetPoWHash() == uint256S("0x00308b444457d0eaaf37e77f9ae271700610665903f2bb4958fb801006e1481c")); // genesis
        assert(consensus.hashGenesisBlock == uint256S("0x32787dd2f835fdf470e01ffcd7c731df5169371af1d8ccaba2b378d743388d66")); // genesis
        assert(genesis.hashMerkleRoot == uint256S("0xe71dc16655132ebaf6b0a2897d676ebbd47d015649027f9c77b84aa33d44fb77"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        // vSeeds.emplace_back("1seed-testnet.cryptozeny.com"); // cryptozeny

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,83);  // legacy: starting with T (upper)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,128); // p2sh-segwit: starting with t (lower)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tadvc";     // bech32: starting with tadvc

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = {
            {
                {0, uint256S("0x32787dd2f835fdf470e01ffcd7c731df5169371af1d8ccaba2b378d743388d66")},
                // {1, uint256S("0741357f5ee729dffdebdc78f0897f4c244788effebb2cda22c5d5947bebd923")},
                // {510, uint256S("9e355f520668f48212641bf674733d24e56c6b2f05ac60ba6fa860163feef8d4")},
                // {511, uint256S("9418cef01af69fc2491afcb56c640df9d78e0d0768bf9e2748c1978d2ffb97ed")},
                // {512, uint256S("c8663700fe1020185d26f1f06571dd51ed2f9c331436b83aa08dd21352f7ffea")},
                // {780811, uint256S("bd83debccee1bef17340539beff64ad3feab03c25e5d91969cf5418b8e2fe5a7")}, // 780811=780301+510
                // {4000000, uint256S("bc05c2d5e81785f287cd58a798b64467cff35c8ef2bbe8062d8420eeb86f4056")},
            }
        };

        // TODO.ADVC.UPDATE
        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 bd83debccee1bef17340539beff64ad3feab03c25e5d91969cf5418b8e2fe5a7 (780811)
            /* nTime    */ 1744230279,
            /* nTxCount */ 1,
            /* dTxRate  */ 0.1692345821801809
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

        // ADVC-HALVING // (was same as BTC)
        consensus.nSubsidyHalvingInterval = 1576800; // every 3 years

        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");

        consensus.nPowTargetTimespan = 61200;

        consensus.nPowAllowMinDifficultyBlocksAfterHeight = boost::none; // DigiShieldZEC
        consensus.nPowAveragingWindow = 17; // DigiShieldZEC // 85/nPowTargetSpacing(5) = 17


        assert(maxUint/UintToArith256(consensus.powLimit) == 17); // DigiShieldZEC // 0x0000000000000000000000000000000000000000000000000000000000000011 == 17
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow); // DigiShieldZEC // true: 17 >= 17

        consensus.nPowMaxAdjustDown = 0; // DigiShieldZEC // Turn off adjustment down
        consensus.nPowMaxAdjustUp = 0; // DigiShieldZEC // Turn off adjustment up

        consensus.nPowTargetSpacing = 60;

        consensus.fPowAllowMinDifficultyBlocks = true; // DigiShieldZEC
        consensus.fPowNoRetargeting = true; // DigiShieldZEC

        // ADVC-HALVING // (was same as BTC)
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains

        // ADVC-HALVING // (was same as BTC)
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); // genesis

        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0x5b;
        pchMessageStart[3] = 0xad;
        nDefaultPort = 45340;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1744230401, 0, 0x200f0f0f, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        

        assert(genesis.GetPoWHash() == uint256S("0x0e352a5b19e9c6dcef629c0c5c241f3b5e79486bdb1fc17dff514cf679d4eb66")); // genesis
        assert(consensus.hashGenesisBlock == uint256S("0x283f95355703e3fa7f2a1593d890966846cf6378d086c5165aac4fef240ac92d")); // genesis
        assert(genesis.hashMerkleRoot == uint256S("0xe71dc16655132ebaf6b0a2897d676ebbd47d015649027f9c77b84aa33d44fb77"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                {0, uint256S("0x283f95355703e3fa7f2a1593d890966846cf6378d086c5165aac4fef240ac92d")}, // genesis
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);  // legacy: starting with R (upper)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,123); // p2sh-segwit: starting with r (lower)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "radvc";    // bech32: starting with radvc
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

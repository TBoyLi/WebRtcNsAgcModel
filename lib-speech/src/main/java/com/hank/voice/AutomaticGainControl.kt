/*
 * 20-1-13 下午3:14 coded form Zhonghua.
 */
package com.hank.voice

/**
 * AGC(自动增益控制)处理模块
 * @author Zhonghua
 */
class AutomaticGainControl {
    /**
     * 创建一个自动增益控制实例
     * @return 创建的自动增益控制实例的指针
     */
    external fun agcCreate(): Long

    /**
     * 释放一个自动增益控制实例
     * @param agcInst 自动增益控制实例的指针
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun agcFree(agcInst: Long): Int

    /**
     * 初始化自动增益控制实例
     * @param agcInst 自动增益控制实例的指针
     * @param minLevel 最小增益级别
     * @param maxLevel 最大增益级别
     * @param agcMode 自动增益控制模式
     * @param fs 采样率
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun agcInit(agcInst: Long, minLevel: Int, maxLevel: Int, agcMode: Int, fs: Int): Int

    /**
     * 设置自动增益控制实例的配置
     * @param agcInst 自动增益控制实例的指针
     * @param targetLevelDbfs 目标音量级别（单位：dBFS）
     * @param compressionGaindB 压缩增益（单位：dB）
     * @param limiterEnable 是否启用限制器
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun agcSetConfig(
        agcInst: Long,
        targetLevelDbfs: Short,
        compressionGaindB: Short,
        limiterEnable: Boolean
    ): Int

    /**
     * 分析音频数据帧，计算增益值
     * @param agcInst 自动增益控制实例的指针
     * @param inNear 近端音频数据
     * @param num_bands 音频数据的频带数量
     * @param samples 音频数据的样本数量
     * @param out 输出音频数据
     * @param inMicLevel 输入麦克风级别
     * @param outMicLevel 输出麦克风级别
     * @param echo 回声消除
     * @param saturationWarning 饱和警告
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun agcProcess(
        agcInst: Long, inNear: ShortArray?, num_bands: Int, samples: Int, out: ShortArray?,
        inMicLevel: Int, outMicLevel: Int, echo: Int, saturationWarning: Boolean
    ): Int

    /**
     * 添加远端音频数据帧，用于计算增益值
     * @param agcInst 自动增益控制实例的指针
     * @param inFar 远端音频数据
     * @param samples 音频数据的样本数量
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun agcAddFarend(agcInst: Long, inFar: ShortArray?, samples: Int): Int

    /**
     * 添加麦克风音频数据帧，用于计算增益值
     * @param agcInst 自动增益控制实例的指针
     * @param inMic 麦克风音频数据
     * @param num_bands 音频数据的频带数量
     * @param samples 音频数据的样本数量
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun agcAddMic(agcInst: Long, inMic: ShortArray?, num_bands: Int, samples: Int): Int

    /**
     * 使用虚拟麦克风音频数据帧，用于计算增益值
     * @param agcInst 自动增益控制实例的指针
     * @param inMic 麦克风音频数据
     * @param num_bands 音频数据的频带数量
     * @param samples 音频数据的样本数量
     * @param micLevelIn 输入麦克风级别
     * @param micLevelOut 输出麦克风级别
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun agcVirtualMic(
        agcInst: Long,
        inMic: ShortArray?,
        num_bands: Int,
        samples: Int,
        micLevelIn: Int,
        micLevelOut: Int
    ): Int

    companion object {
        init {
            System.loadLibrary("legacy_agc-lib")
        }
    }
}
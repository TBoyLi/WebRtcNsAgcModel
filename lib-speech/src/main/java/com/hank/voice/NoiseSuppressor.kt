/*
 * 20-1-13 下午3:12 coded form Zhonghua.
 */
package com.hank.voice

/**
 * NS(降噪)处理模块
 * @author Zhonghua
 */
class NoiseSuppressor {
    /**
     * 创建一个降噪处理器实例
     * @return 创建的降噪处理器实例的指针
     */
    external fun nsCreate(): Long

    /**
     * 初始化降噪处理器实例
     * @param nsHandler 降噪处理器实例的指针
     * @param frequency 采样频率
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun nsInit(nsHandler: Long, frequency: Int): Int

    /**
     * 设置降噪处理器的策略
     * @param nsHandler 降噪处理器��例的指针
     * @param mode 降噪模式（0: Mild, 1: Medium , 2: Aggressive）
     * @return 如果成功，返回0，如果出错，返回-1
     */
    external fun nsSetPolicy(nsHandler: Long, mode: Int): Int

    /**
     * 使用降噪处理器处理音频数据帧
     * @param nsHandler 降噪处理器实例的指针
     * @param spframe 输入的音频数据帧
     * @param num_bands 音频数据的频带数量
     * @param outframe 输出的音频数据帧
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun nsProcess(
        nsHandler: Long,
        spframe: FloatArray?,
        num_bands: Int,
        outframe: FloatArray?
    ): Int

    /**
     * 释放降噪处理器实例
     * @param nsHandler 降噪处理器实例的指针
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun nsFree(nsHandler: Long): Int

    /**
     * 创建一个扩展降噪（Nsx）模块实例
     * @return 创建的扩展降噪（Nsx）模块实例的指针
     */
    external fun nsxCreate(): Long

    /**
     * 初始化扩展降噪（Nsx）模块实例
     * @param nsxHandler 扩展降噪（Nsx）模块实例的指针
     * @param frequency 采样频率
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun nsxInit(nsxHandler: Long, frequency: Int): Int

    /**
     * 为扩展降噪（Nsx）模块实例设置策略
     * @param nsxHandler 扩展降噪（Nsx）模块实例的指针
     * @param mode 降噪模式（0: Mild, 1: Medium , 2: Aggressive）
     * @return 如果成功，返回0，如果出错，返回-1
     */
    external fun nsxSetPolicy(nsxHandler: Long, mode: Int): Int

    /**
     * 使用扩展降噪（Nsx）模块处理音频数据帧
     * @param nsxHandler 扩展降噪（Nsx）模块实例的指针
     * @param speechFrame 输入的音频数据帧
     * @param num_bands 音频数据的频带数量
     * @param outframe 输出的音频数据帧
     * @return 如果成功，返回0，如果处理器���空，返回-3
     */
    external fun nsxProcess(
        nsxHandler: Long,
        speechFrame: ShortArray?,
        num_bands: Int,
        outframe: ShortArray?
    ): Int

    /**
     * 释放扩展降噪（Nsx）模块实例
     * @param nsxHandler 扩展降噪（Nsx）模块实例的指针
     * @return 如果成功，返回0，如果处理器为空，返回-3
     */
    external fun nsxFree(nsxHandler: Long): Int

    companion object {
        init {
            System.loadLibrary("legacy_ns-lib")
        }
    }
}
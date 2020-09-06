package com.utkin.analyzerapp

import android.app.Application
import android.content.Context

class AnalyzerApp : Application() {
    override fun onCreate() {
        super.onCreate()
        context = this
    }

    companion object {
        var context: Context? = null
            private set
    }
}
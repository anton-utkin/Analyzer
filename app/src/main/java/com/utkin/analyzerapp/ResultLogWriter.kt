package com.utkin.analyzerapp

import android.util.Log;
import com.utkin.analyzerapp.Constants.Companion.PRODUCTION

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

class ResultLogWriter {
    private val TAG = ResultLogWriter::class.simpleName;

    private val RESULTS_FILE =
        com.utkin.analyzerapp.AnalyzerApp.context?.getApplicationInfo()?.dataDir + "/results.txt";
    private var mOutput: OutputStream? = null;

    public fun init() {
        if (!PRODUCTION) {
            Log.i(TAG, "file path: " + RESULTS_FILE);
        }
        try {
            mOutput = FileOutputStream(RESULTS_FILE);
        } catch (e: IOException) {
            if (!PRODUCTION) {
                Log.e(TAG, "Error: " + e.toString());
            }
        }
    }

    public fun deinit() {
        try {
            mOutput?.flush();
            mOutput?.close();
        } catch (e: IOException) {
            if (!PRODUCTION) {
                Log.e(TAG, "Error: " + e.toString());
            }
        }
    }

    public fun write(line: String) {
        try {
            var lineWithEnding = line + '\n';
            var data: ByteArray = lineWithEnding.toByteArray();
            if (!PRODUCTION) {
                Log.i(TAG, "write to results.txt line: " + line);
            }
            mOutput?.write(data, 0, data.size);
        } catch (e: IOException) {
            if (!PRODUCTION) {
                Log.e(TAG, "Error: " + e.toString());
            }
        }
    }
}

package com.utkin.analyzerapp

class AnalyzerListItem {
    var mTitle: String;

    constructor (title: String) {
        mTitle = title;
    }

    fun setTitle(title: String) {
        mTitle = title;
    }

    fun getTitle(): String {
        return mTitle;
    }
}
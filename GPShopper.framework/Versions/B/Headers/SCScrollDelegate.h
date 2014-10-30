//
//  SCScrollDelegate.h
//  EXPproject
//
//  Created by kimberly on 7/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@protocol SCScrollEntry < NSObject, NSCopying >

-(CGSize)size;
-(NSString *)reuseIdentifier;
-(UIView *)view;
-(void)configureView: (UIView *)v;

@end

@interface SCBaseScrollEntry : NSObject < SCScrollEntry >

@property (readwrite) CGSize size;
@property (copy) NSString *reuseIdentifier;
@property (copy) NSString *xibFilename;

@end


@interface SCScrollEntryAtOffset : NSObject

@property (retain) id< SCScrollEntry > entry;
@property (readwrite) CGPoint offset;

@end


@protocol SCScrollSubview <NSObject>

-(NSString *)reuseIdentifier;

@end


enum SCScrollLayoutAlign
{
    SCScrollLayoutAlignTop=1,
    SCScrollLayoutAlignLeft=2
};


@interface SCGridScrollDelegate : NSObject < UIScrollViewDelegate >
{
    NSMutableDictionary *entryToView;
    NSMutableArray *entriesAtOffset;
    NSMutableDictionary *reuseIdentifierToCachedViews;
    
    CGPoint currentOffset;
}

@property (readwrite) double maxWidth;
@property (readwrite) double maxHeight;
@property (readwrite) double inset;
@property (readwrite) double space;
@property (readwrite) enum SCScrollLayoutAlign align;

@property (readwrite) double updateDistance;

-(void)addEntry: (id< SCScrollEntry >)e;
-(void)addEntries: (NSArray *)es;
-(void)removeAllEntries;

-(void)populateScrollView: (UIScrollView *)sv;

-(CGPoint)offsetForEntry: (id<SCScrollEntry>)en
      afterEntryAtOffset: (SCScrollEntryAtOffset *)enoff;

-(CGSize)contentSize;

@end

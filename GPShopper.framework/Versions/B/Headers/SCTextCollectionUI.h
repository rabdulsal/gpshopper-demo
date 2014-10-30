//
//  SCTextCollectionUI.h
//  feature
//
//  Created by kimberly on 9/27/13.
//  Copyright (c) 2013 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface SCTextCollectionEntryBuilder : NSObject
{
    NSMutableArray *entries;
}
@property (retain) UIColor *currentTextColor;
@property (retain) UIFont *currentFont;
@property (readwrite) double width;
@property (readonly) double totalHeight;

-(void)addEntryForString: (NSString *)t;
-(void)addEntryForString: (NSString *)t
               maxHeight: (double)h;
-(void)addSpaceOfHeight: (double)h;
-(void)addFullWidthEntryForString: (NSString *)t;

-(void)removeAllEntries;
-(NSArray *)entries;

-(UILabel *)newLabelForString: (NSString *)t;
-(void)addEntryForSubview: (UIView *)v;

@end

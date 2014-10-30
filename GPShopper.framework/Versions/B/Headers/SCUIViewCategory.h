//
//  SCViewCategory.h
//  bestbuy
//
//  Created by kimberly on 4/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


enum SCViewLayoutHAlign
{
    SCViewLayoutHAlignLeft=1,
    SCViewLayoutHAlignCenter=2,
    SCViewLayoutHAlignRight=3,
    SCViewLayoutHAlignNone=4
};

@interface UIView ( SCUIViewHierarcy )

-(UIView *)depthFirstSubviewOfClass: (Class)c
                           maxDepth: (uint)md;

-(void)horizontallyAddSubview: (UIView *)v
                      spacing: (double)s;

-(void)verticallyAddSubview: (UIView *)v
                    spacing: (double)s;

-(void)verticallyAddSubview: (UIView *)v
                    spacing: (double)s
                     halign: (enum SCViewLayoutHAlign)a;

-(void)verticallyAddSubview: (UIView *)v
                    spacing: (double)s
      ignoreNonintersecting: (BOOL)i;

- (void)addSubview:(UIView *)v
            hSpace:(CGFloat)hSpace
            vSpace:(CGFloat)vSpace;

- (void)addGridSquaresOfLength:(CGFloat)length;

-(CGPoint)maxSubviewCorner;
-(void)maxViewHeight;
-(void)setHeight:(CGFloat)h;
-(void)addExtraViewHeight:(CGFloat)h;

-(void)setFrameOrigin: (CGPoint)p;

-(void)removeAllSubviews;

-(double)widthFraction: (double)f;
-(double)heightFraction: (double)f;

-(CGPoint)origin;

-(void)horizontallyCenterInSuperview;

-(void)verticallyAddLabelWithText: (NSString *)s
                       widthRange: (NSRange)r
                             font: (UIFont *)f
                          spacing: (double)d
            ignoreNonintersecting: (BOOL)i;

@end

@interface UIView ( SCUIViewAnimateSubViews )
-(void)slideUpToShowView:(UIView *)slide show:(BOOL)show;
@end


@interface UIView (FirstResponder)
- (UIView *)findFirstResponder;
- (BOOL)findAndResignFirstResponder;
@end


@interface UILabel ( SCUILabel )

-(void)resizeToMaxWidth: (double)w;

+(UILabel *)newLabelWithText: (NSString *)s
                  widthRange: (NSRange)r
                        font: (UIFont *)f;

+(UILabel *)newLabelWithText: (NSString *)s
                  widthRange: (NSRange)r
                        font: (UIFont *)f
              constrainWidth: (BOOL)c;

+(UILabel *)newLabelWithText: (NSString *)s
                  widthRange: (NSRange)r
                        font: (UIFont *)f
                   textColor: (UIColor *)tc;

+(UILabel *)newLabelWithText: (NSString *)s
                  widthRange: (NSRange)r
                        font: (UIFont *)f
                   textColor:(UIColor *)tc
              constrainWidth: (BOOL)c;

+(UILabel *)newLabelWithText: (NSString *)s
                  widthRange: (NSRange)r
                        font: (UIFont *)f
                   textColor:(UIColor *)tc
             backgroundColor: (UIColor *)bc
              constrainWidth: (BOOL)c;


-(void)maxNibLabelHeightWithText:(NSString *)s;
-(void)maxNibLabelHeightWithText:(NSString *)s numberOfLines:(int)line labelHeight:(CGFloat)h;
-(CGFloat)maxCornerheight;
-(void)setY:(CGFloat)y;
-(void)maxWidthFromText:(NSString *)s;
-(CGFloat)getMaxWidthCorner;

@end


@interface SCInsetLabel : UILabel
@property (readwrite) UIEdgeInsets insets;
@end

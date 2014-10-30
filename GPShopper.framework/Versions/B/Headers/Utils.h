//
//  Logger.h
//  Slifter_iphone_rewrite
//
//  Created by kimberly on 10/13/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#ifndef UTILS_H
#define UTILS_H

#import <UIKit/UIKit.h>

@interface Logger : NSObject
{
	NSObject *owner;
	NSUInteger noisiness;
	NSString *shortName;
	BOOL logPointer;
	BOOL logRetainCount;
}

@property (nonatomic, assign) NSObject *owner;
@property (nonatomic) NSUInteger noisiness;
@property (nonatomic, retain) NSString *shortName;
@property (nonatomic) BOOL logPointer;
@property (nonatomic) BOOL logRetainCount;

-(id)initWithOwner: (NSObject *)o
		noiseLevel: (NSUInteger)nl;

-(void)log: (NSUInteger)noiseLevel
   content: (NSString *)format, ...;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface NamedAttribute : NSObject < NSCopying >
{
	NSString *name;
	NSString *val;
}
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *val;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface GraphicsUtil : NSObject

{}

+(UIImageView *)newImageViewWithFilename: (NSString *)filename;

+(UIImageView *)newImageViewWithImage: (UIImage *)image
							  maxSize: (CGSize)size;

+(UIImage *)newImageWithURL: (NSString *)s;

+(UIImage *)newImageWithFilename: (NSString *)filename;

+(UIColor *)newColorWithFilename: (NSString *)filename;

+(void)setBackgroundColorFor: (UIView *)view
					filename: (NSString *)filename;

+(void)clearCell: (UITableViewCell *)cell;

+(UIColor *)newColorWithHexString: (NSString *)hs;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface TextUtil : NSObject
{}

+(NSString *)newStringFrom: (NSString *)s
			   truncatedTo: (int)t;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface ContainerUtil : NSObject

{}

+(void)setObject: (NSObject *)object
	inDictionary: (NSMutableDictionary *)dictionary
	  integerKey: (uint64_t)key;

+(id)objectFromDictionary: (NSMutableDictionary *)dictionary
			   integerKey: (uint64_t)key;

+(void)removeObjectFromDictionary: (NSMutableDictionary *)dictionary
					   integerKey: (uint64_t)key;

+(void)addInteger: (uint64_t)i
		  toArray: (NSMutableArray *)arr;

+(void)addUniqueInteger: (uint64_t)i
				toArray: (NSMutableArray *)arr;

+(void)setInteger: (uint64_t)i
		  atIndex: (int)j
		  ofArray: (NSMutableArray *)arr;

+(uint64_t)integerAtIndex: (int)j
				  ofArray: (NSArray *)arr;

+(uint64_t)integerAtKey: (uint64_t)key
		   ofDictionary: (NSDictionary *)dictionary;

+(uint64_t)integerAtStrKey: (NSString *)key
			  ofDictionary: (NSDictionary *)dictionary;

+(uint64_t)setInteger: (uint64_t)value
				atKey: (uint64_t)key
		 ofDictionary: (NSMutableDictionary *)dictionary;

@end


//-----------------------------------------------------------------
//-----------------------------------------------------------------


@class LabelStyle;

// TODO: make hierarchy of label style names?  eh.
@interface CustomGlobals : NSObject
{}

+(NSDictionary *)labelStyles;
+(NSDictionary *)colors;

+(LabelStyle *)labelStyleNamed: (NSString *)n;
+(UIColor *)colorNamed: (NSString *)n;
+(UITableViewCellSelectionStyle)cellSelectionStyle;
+(NSString *)rssListFeedUrl;
+(uint64_t)maxNumSearchResults;
+(NSArray *)tabOrder;
+(NSDictionary *)infoForTab: (int)i;
+(NSString *)pageTypeForTab: (int)i;
+(NSString *)nameForTab: (int)i;
+(NSString *)imageFilenameForTab: (int)i;
+(NSDictionary *)pageDetails;
+(NSDictionary *)detailsForPage: (NSString *)page;
+(NSString *)titleForPage: (NSString *)page;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------

/*
@interface UrlImageCache : NSObject

+(void)setUrlPrefix: (NSString *)prefix;
+(void)setNumCacheDays: (uint64_t)ncd;
+(NSString *)newUrlForHash: (NSData *)hash;
+(NSString *)newUrlForHashStr: (NSString *)hash;
+(UIImage *)imageForUrl: (NSString *)url
				   wait: (BOOL)wait;
+(UIImage *)imageForHashStr: (NSString *)hash
					   wait: (BOOL)wait;
+(UIImage *)localImageForHashStr: (NSString *)hash;
+(void)cacheUrl: (NSString *)url;
+(void)printHistoryToLog;

@end
*/

//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface FramedObject: NSObject
{}

-(CGRect)frame;
-(void)setFrame: (CGRect)f;

-(void)putIntoView: (UIView *)view
		  atOffset: (CGPoint)offset;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface FramedRect : FramedObject
{
	CGRect frame;
}

-(id)initWithSize: (CGSize)s;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface FramedView : FramedObject
{
	UIView *internalView;
}

-(id)initWithView: (UIView *)v;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------

enum LayoutStyle
{
	LayoutStyleVertical,
	LayoutStyleHorizontal,
	LayoutStyleVerticalCentered,
	LayoutStyleHorizontalCentered
};

@interface BaseFrameArray : FramedRect
{
	NSMutableArray *framedObjects;
	NSUInteger layoutStyle;
}

-(id)initWithLayoutStyle: (NSUInteger)s;

-(BOOL)vertical;
-(BOOL)horizontal;
-(BOOL)centered;

-(void)addFramedObject: (FramedObject *)fo;
-(void)addView: (UIView *)view;
-(void)addSpace: (double)space;
-(void)addJump: (double)jump;
-(void)addArray: (BaseFrameArray *)arr;
-(void)addRect: (CGSize)size;

-(BOOL)empty;
-(void)clear;

-(void)putIntoView: (UIView *)view
		  atOffset: (CGPoint)offset;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface LabelStyle : NSObject
{
	CGFloat fontSize;
	BOOL bold;
	BOOL italic;
	BOOL trim;
	UIColor *color;
	UIColor *backgroundColor;
	NSTextAlignment textAlignment;
}

@property (nonatomic) CGFloat fontSize;
@property (nonatomic) BOOL bold;
@property (nonatomic) BOOL italic;
@property (nonatomic) BOOL trim;
@property (nonatomic, retain) UIColor *color;
@property (nonatomic, retain) UIColor *backgroundColor;
@property (nonatomic) NSTextAlignment textAlignment;

-(UILabel *)newLabelWithText: (NSString *)s
                    maxWidth: (double)w;

@end


//--------------------------------------------------------------------
//--------------------------------------------------------------------


@interface FrameArray : BaseFrameArray
{
    NSUInteger defaultMaxHeight;
    NSUInteger defaultNumLines;
}

@property (assign) NSUInteger defaultMaxHeight;
@property (assign) NSUInteger defaultNumLines;

-(id)initWithStyle: (NSUInteger)s;

-(void)newLabel: (NSString *)text
		  width: (NSUInteger)maxWidth
		  style: (LabelStyle *)style;

-(void)newButtonWithImage: (UIImage *)image
				   target: (id)target
				   action: (SEL)action;

-(void)newImageView: (UIImage *)image;

+(UIButton *)newButtonWithImage: (UIImage *)image
						 target: (id)target
						 action: (SEL)action;

@end


// Here to maintain backwards compatibility.
// Instances of this class should be removed when convenient.
// Use FrameArray instead.
@interface ConstructorFrameArray : FrameArray
{}

@end

#endif
